from dataset_generator import *
import tensorflow as tf
from tensorflow.keras.models import Sequential, load_model, save_model, Model
from tensorflow.keras.layers import Dense, GRU, Lambda, Activation, Input
from tensorflow.keras.callbacks import TensorBoard,ModelCheckpoint
from tensorflow.keras.backend import ctc_batch_cost
from tensorflow.keras import optimizers
import time


def write_log(callback, names, logs, batch_no):
    for name, value in zip(names, logs):
        summary = tf.Summary()
        summary_value = summary.value.add()
        summary_value.simple_value = value
        summary_value.tag = name
        callback.writer.add_summary(summary, batch_no)
        callback.writer.flush()
"""
def model(GRU_size=5):
    adam = optimizers.Adam()
    model = Sequential()
    model.add(GRU(GRU_size))
    model.add(Dense(len(interested_words), activation='softmax'))
    model.compile(loss='categorical_crossentropy', optimizer=adam)
    return model
"""
"""
def train(model = model(),checkpoint = "latest.hdf5"):
    dataset = build_dataset()
    callback = TensorBoard("_tensor_board")
    callback.set_model(model)
    labels = interested_words
    for i in range(10000):
        save_model(model, checkpoint)
        print("Chunk "+str(i)+" of 10000...")
        X,Y = get_batch(dataset,batchsize=1500)
        for j in range(10):
            logs = model.train_on_batch(np.array(X),np.array(Y))
            print("loss:",logs)
            write_log(callback, ["training loss"], [logs], i*10+j)
        
        X,Y = get_batch(dataset,batchsize=100,batchtype="test")
        results = model.predict(X)
        accuracy = 0
        for result,actual in zip(results,Y):
            #print("running test")
            x = np.argmax(result)
            j = np.argmax(actual)
            try:
                print("expected "+labels[j]," got "+labels[x])
            except:
                pass
            if x == j: accuracy += 1
        write_log(callback,["test accuracy"],[accuracy],i)


if __name__ == "__main__":

    os.chdir("C:\\users\\arjo1\\documents\\data_google_speech")
    train()
"""
os.chdir("C:\\users\\arjo1\\documents\\data_google_speech")

graph = tf.Graph()
with graph.as_default():
    inputs = tf.placeholder(tf.float32, [None, None, 2], name="input")
    targets = tf.sparse_placeholder(tf.int32, name="expected_sequence")
    seq_len = tf.placeholder(tf.int32, [None], name="length")
    cell = tf.nn.rnn_cell.GRUCell(5)
    output, _ = tf.nn.dynamic_rnn(cell, inputs, seq_len, dtype=tf.float32)
    shape = tf.shape(inputs)
    batch_s, max_timesteps = shape[0], shape[1]
    outputs = tf.reshape(output, [-1, 5])
    W = tf.Variable(tf.truncated_normal([5,
                                        6],
                                    stddev=0.1))
    b = tf.Variable(tf.constant(0., shape=[6]))
    logits = tf.matmul(outputs, W) + b
    logits = tf.reshape(logits, [batch_s, -1, 6])
    logits = tf.transpose(logits, (1, 0, 2))
    loss = tf.nn.ctc_loss(targets, logits, seq_len)
    cost = tf.reduce_mean(loss)
    optimizer = tf.train.MomentumOptimizer(0.01,0.9).minimize(cost)
    decoded, log_prob = tf.nn.ctc_greedy_decoder(logits, seq_len)
    ler = tf.reduce_mean(tf.edit_distance(tf.cast(decoded[0], tf.int32),
                                        targets))


with tf.Session(graph=graph) as session:
    # Initializate the weights and biases
    tf.global_variables_initializer().run()
    dataset = build_dataset()
    for curr_epoch in range(100):
        train_cost = train_ler = 0
        start = time.time()

        for batch in range(10):
            train_inputs, train_targets, train_seq_len = get_batch(dataset, 15)
            idx = tf.where(tf.not_equal(train_targets, 0)) 
            sparse = tf.SparseTensor(idx, tf.gather_nd(train_targets, idx),train_targets.shape)
            feed = {inputs: train_inputs,
                    targets: session.run(sparse),
                    seq_len: train_seq_len}
            batch_cost, _ = session.run([cost, optimizer], feed)
            train_cost = batch_cost*1500
            train_ler = session.run(ler, feed_dict=feed)*1500
            log = "Epoch {}/{}, train_cost = {:.3f}, train_ler = {:.3f}, time = {:.3f}"
            print(log.format(curr_epoch+1, 100, train_cost, train_ler, time.time() - start))
        
        