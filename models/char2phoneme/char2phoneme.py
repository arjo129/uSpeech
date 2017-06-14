import numpy
import tensorflow as tf


def build_dict_repr(filename):
    keys = {}
    with open(filename, newline="\n") as f:
        for line in f:
            my_key = line
            keys[my_key] = None
    num_keys = len(keys.keys())
    i = 0
    for k in keys.keys():
        keys[k] = numpy.array([0]*num_keys)
        keys[k][i] = 1
        i += 1
    return keys

def char2vec(string):
    my_arr = []
    for c in string:
        arr = numpy.array([0]*128)
        arr[ord(c)] = 1
        my_arr.append(arr)
    return arr

def phoneme2vec(phonemes, dct):
    my_arr = []
    for p in phonemes:
        my_arr.append(dct[p])
    return my_arr

def convert_dict_to_vec(filename):
    with open(filename) as f:
        for line in f:
            if line[0] not in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
                continue
            else:
                datum = line.split(" ")
                word = datum[0]
                pronunciation = []
                for i in datum[1:]:
                    if i != "":
                        if i[-1] == "\n":
                            i = i[:-1]
                        pronunciation.append(i)
                yield word, pronunciation

if __name__ == "__main__":
    labels = build_dict_repr("data\cmudict-0.7b.symbols")
    graph = tf.Graph()
    num_classes = len(labels)
    num_hidden = 50
    num_epochs = 200
    batch_size = 20
    with graph.as_default():
        inputs = tf.placeholder(tf.float32, [None, None, 128])
        targets = tf.sparse_placeholder(tf.int32)
        seq_len = tf.placeholder(tf.int32, [None])
        cell = tf.contrib.rnn.GRUCell(num_hidden, state_is_tuple=True)
        stack = tf.contrib.rnn.MultiRNNCell([cell], state_is_tuple=True)
        outputs, _ = tf.nn.dynamic_rnn(stack, inputs, seq_len, dtype=tf.float32)
        shape = tf.shape(inputs)
        batch_s, max_timesteps = shape[0], shape[1]
        outputs = tf.reshape(outputs, [-1, num_hidden])
        W = tf.Variable(tf.truncated_normal([num_hidden,num_classes],stddev=0.1))
        b = tf.Variable(tf.constant(0,shape=[num_classes]))
        prediction = tf.matmul(output,W)+b
        prediction = tf.reshape(prediction, [batch_size, -1,num_classes])
        prediction = tf.transpose(prediction, (1,0,2))
        loss = tf.ctc_loss(logits, targets, seq_len)
        cost = tf.reduce_mean(loss)
        optimizer = tf.train.AdamOptimizer()
    with tf.Session(graph=graph) as session:
        tf.global_variables_initializer().run()
        for curr_epoch in range(num_epochs):
            train_cost = train_ler = 0
            for batch in range(num_batches_per_epoch):
                feed = { input:}
        
