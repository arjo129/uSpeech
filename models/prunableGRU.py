import tensorflow as tf
import numpy as np
from dataset_generator import *
from tensorflow.contrib.rnn import RNNCell, static_rnn
from tensorflow.python.ops import variable_scope as vs
from tensorflow.python.ops import math_ops
from tensorflow.python.framework.ops import convert_to_tensor

def get_mask(arr, thresh=0.1):
    return np.greater(abs(arr),thresh)*1

class PrunableGRU(RNNCell):
    def __init__(self,W,U,bias,thresh=0.1):
        self.input_sz = W.shape[0]
        unit_size = W.shape[1]//3
        self.W_z = W[:,:unit_size]
        self.W_z_mask = tf.constant(get_mask(W[:,:unit_size],thresh),dtype=tf.float32)
        self.W_r = W[:,unit_size:unit_size*2]
        self.W_r_mask = tf.constant(get_mask(W[:,unit_size:unit_size*2],thresh),dtype=tf.float32)
        self.W_h = W[:,unit_size*2:]
        self.W_h_mask = tf.constant(get_mask(W[:,unit_size*2:],thresh),dtype=tf.float32)
        self.U_z = U[:,:unit_size]
        self.U_z_mask = tf.constant(get_mask(U[:,:unit_size],thresh),dtype=tf.float32)
        self.U_r = U[:,unit_size:unit_size*2]
        self.U_r_mask = tf.constant(get_mask(U[:,unit_size:unit_size*2],thresh),dtype=tf.float32)
        self.U_h = U[:,unit_size*2:]
        self.U_h_mask = tf.constant(get_mask(U[:,unit_size*2:],thresh),dtype=tf.float32)
        self.b_z = bias[:unit_size]
        self.b_r = bias[unit_size:unit_size*2]
        self.b_h = bias[unit_size*2:]
        self._num_units = unit_size
    @property
    def output_size(self):
        return self._num_units
    @property
    def state_size(self):
        return self._num_units
    def zero_state(self, batchsize, dtype):
        return tf.ones([batchsize, self.state_size],dtype=dtype)
    def __call__(self,inputs, state, scope=None):
        inputs = convert_to_tensor(inputs)
        with vs.variable_scope(scope or type(self).__name__):
            W_z = tf.Variable(self.W_z,name="W_z")
            W_r = tf.Variable(self.W_r,name="W_r")
            W_h = tf.Variable(self.W_h,name="W_h")
            U_z = tf.Variable(self.U_z,name="U_z")
            U_r = tf.Variable(self.U_r,name="U_r")
            U_h = tf.Variable(self.U_h,name="U_h")
            b_z = tf.Variable(self.b_z,name="b_z")
            b_r = tf.Variable(self.b_r,name="b_r")
            b_h = tf.Variable(self.b_h,name="b_h")
            z = math_ops.sigmoid(math_ops.matmul(inputs,W_z*self.W_z_mask)+math_ops.matmul(state,self.U_z_mask*U_z)+self.b_z)
            r = math_ops.sigmoid(math_ops.matmul(inputs,W_r*self.W_r_mask)+math_ops.matmul(state,self.U_r_mask*U_r)+self.b_r)
            hh = math_ops.tanh(math_ops.matmul(inputs,W_h)+math_ops.matmul(state*r,U_h)+self.b_h)
            h = (1-z)*hh + z*state
        return h,h

class PrunableLogits:
    def __init__(self,W,bias,dtype="float32"):
        self.weights = tf.Variable(W,name="output_weight")
        self.bias = tf.Variable(bias)
        self.w_mask = tf.constant(get_mask(W),dtype=dtype)
    def __call__(self,inputs):
        return tf.matmul(inputs,self.weights*self.w_mask)+self.bias
    
def prune_model(model,batchsize = 50):
    weights = model.get_weights()
    W = weights[0]
    U = weights[1]
    bias = weights[2]
    W_out = weights[3]
    bias_out = weights[4]
    GRU = PrunableGRU(W,U,bias)
    Logits = PrunableLogits(W_out,bias_out)
    X = tf.placeholder("float", [40, batchsize, 2])
    Y = tf.placeholder("float", [None, W_out.shape[1]])
    x = tf.unstack(X,axis=0)
    outputs, states = static_rnn(GRU, x, dtype=tf.float32)
    logits = Logits(outputs[-1])
    prediction = tf.nn.softmax(logits)
    loss_op = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=logits, labels=Y))
    optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.001)
    train_op = optimizer.minimize(loss_op)
    correct_pred = tf.equal(tf.argmax(prediction, 1), tf.argmax(Y, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))
    init = tf.global_variables_initializer()
    dataset = build_dataset()
    with tf.Session() as sess:
        sess.run(init)
        for i in range(1000):
            batch_x, batch_y = get_batch(dataset,batchsize=batchsize,batchtype="train")
            batch_x = np.swapaxes(batch_x,1,0)
            sess.run(train_op, feed_dict={X: batch_x, Y: batch_y})
            loss, acc = sess.run([loss_op, accuracy], feed_dict={X: batch_x,Y: batch_y})
            print(loss)
if __name__=="__main__":
    from keras.models import load_model
    import os
    os.chdir("C:\\users\\arjo1\\documents\\data_google_speech")
    model = load_model("gru40.hdf5")
    prune_model(model)
