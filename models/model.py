from dataset_generator import *
import tensorflow as tf
from tensorflow.keras.models import Sequential, load_model, save_model
from tensorflow.keras.layers import LSTM, Dropout, Dense, Bidirectional,GRU
from tensorflow.keras.callbacks import TensorBoard,ModelCheckpoint
from tensorflow.keras import optimizers

def write_log(callback, names, logs, batch_no):
    for name, value in zip(names, logs):
        summary = tf.Summary()
        summary_value = summary.value.add()
        summary_value.simple_value = value
        summary_value.tag = name
        callback.writer.add_summary(summary, batch_no)
        callback.writer.flush()
        
def model(GRU_size=5):
    adam = optimizers.Adam()
    model = Sequential()
    model.add(GRU(GRU_size))
    model.add(Dense(len(interested_words), activation='softmax'))
    model.compile(loss='categorical_crossentropy', optimizer=adam)
    return model

def train(model = model(),checkpoint = "latest.hdf5"):
    dataset = build_dataset()
    callback = TensorBoard("_tensor_board")
    callback.set_model(model)
    labels = interested_words
    for i in range(10000):
        save_model(model, "checkpoint.model")
        print("Chunk "+str(i)+" of 10000...")
        X,Y = get_batch(dataset,batchsize=1000)
        for j in range(10):
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

if __name__ == "__main__":
    os.chdir("C:\\users\\arjo1\\documents\\data_google_speech")
    train()
