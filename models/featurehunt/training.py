#!/usr/bin/python3

import wave,struct
import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from keras.layers.convolutional import Conv1D
from keras.layers.convolutional import UpSampling1D
from keras.layers.pooling import AveragePooling1D

def read_wav(filename):
        file = wave.open(filename)
        arr = []
        for i in range(w.getnframes()):
                frame = w.readframes(1)
                data = struct.unpack("<h", waveData)
                arr.append(int(data[0]))
        return arr

