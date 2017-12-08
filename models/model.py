from dataset_generator import *
import tensorflow as tf
from keras.models import Sequential,load_model
from keras.layers import LSTM, Dropout, Dense, Bidirectional,GRU
from keras.callbacks import TensorBoard,ModelCheckpoint
from keras import optimizers

def write_log(callback, names, logs, batch_no):
    for name, value in zip(names, logs):
        summary = tf.Summary()
        summary_value = summary.value.add()
        summary_value.simple_value = value
        summary_value.tag = name
        callback.writer.add_summary(summary, batch_no)
        callback.writer.flush()
        
def model():
    adam = optimizers.adam(lr=0.05)
    model = Sequential()
    model.add(Bidirectional(LSTM(20), input_shape=(None, 2)))
    model.add(Dense(len(interested_words), activation='softmax'))
    model.compile(loss='categorical_crossentropy', optimizer=adam)
    return model

def train(model = model()):
    dataset = build_dataset()
    callback = TensorBoard("_tensor_board")
    callback.set_model(model)
    labels = interested_words
    for i in range(10000):
        model.save("latest.hdf5")
        print("Chunk "+str(i)+" of 10000...")
        X,Y = get_batch(dataset,batchsize=100)
        for j in range(10):
            #print(np.shape(X))
            logs = model.train_on_batch(np.array(X),np.array(Y))
            print("loss:",logs)
            write_log(callback, ["training loss"], [logs], i*10+j)
        X,Y = get_batch(dataset,batchsize=100,batchtype="test")
        results = model.predict(X)
        accuracy = 0
        for result,actual in zip(results,Y):
            #print("running test")
            x =np.argmax(result)
            j =np.argmax(actual)
            try:
                print("expected "+labels[j]," got "+labels[x])
            except:
                pass
            if x == j: accuracy += 1
        write_log(callback,["test accuracy"],[accuracy],i)
            
train()
