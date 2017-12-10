from tensorflow.python.ops import rnn_cell_impl
from tensorflow.python.ops import variable_scope as vs
from tensorflow.python.ops import math_ops
from tensorflow.python.framework.ops import convert_to_tensor

class PrunableGRU(rnn_cell_impl.RNNCell):
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
    def __call__(self,inputs, state, scope=None):
        inputs = convert_to_tensor(inputs)
        with vs.variable_scope(scope or type(self).__name__):
            W_z = tf.Variable(self.W_z,name="W_z")
            W_r = tf.Variable(self.W_r,name="W_r")
            W_h = tf.Variable(self.W_h,name="W_h")
            U_z = tf.Variable(self.U_z,name="U_z")
            U_r = tf.Variable(self.U_r,name="U_r")
            U_z = tf.Variable(self.U_h,name="U_z")
            b_z = tf.Variable(self.b_z,name="b_z")
            b_r = tf.Variable(self.b_r,name="b_r")
            b_h = tf.Variable(self.b_h,name="b_h")
            z = math_ops.sigmoid(math_ops.matmul(inputs,W_z*self.W_z_mask)+math_ops.matmul(state,self.U_z_mask*U_z)+self.b_z)
            r = math_ops.sigmoid(math_ops.matmul(inputs,W_r*self.W_r_mask)+math_ops.matmul(state,self.U_r_mask*U_r)+self.b_r)
            hh = math_ops.tanh(math_ops.matmul(inputs,W_h)+math_ops.matmul(state*r,U_h)+self.b_h)
            h = (1-z)*hh + z*state
        return h,h
