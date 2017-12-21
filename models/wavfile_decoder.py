import wave
import numpy as np
import struct
import scipy.fftpack as sp

def wav2arr(file):
    nparray = []
    wavfile = wave.open(file)
    if wavfile.getnchannels() == 1:
        for i in range(0,wavfile.getnframes()):
            wavedata = wavfile.readframes(1)
            data = struct.unpack("<h", wavedata)
            nparray.append(data[0])
    return nparray


def get_uspeech_vec(array):
    arr = []
    max_power = 0
    for index in range(0,len(array),400):
        chunk = array[index:index+400]
        power = sum(map(abs,chunk))
        if power > max_power: max_power = power
        difference = 0
        for fpointer in range(1,len(chunk)):
            difference += abs(chunk[fpointer-1]-chunk[fpointer])
        if power != 0:
            arr.append(np.array([power,difference/power]))
        else:
            arr.append(np.array([0,0]))
    for i in range(0,len(arr)):
        arr[i][0] = arr[i][0]/(max_power+1e-19)
    return arr

def hz2mel(hz):
    return 2595*np.log10(1+hz/700)

def mel2hz(mel):
    return 700*10**((mel/2595)-1)

def mel_spectra(array, numcep=13, banks=22, nyquist_freq=8000,NFFT=512):
    fft = np.square(np.absolute(np.fft.rfft(array,NFFT)))*1.0/NFFT
    lowmel = hz2mel(0)
    highmel = hz2mel(nyquist_freq)
    melpoints = np.linspace(lowmel,highmel,22)
    fft_bins = list(map(int,np.floor((NFFT+1)*mel2hz(melpoints)/nyquist_freq)))
    filter_bank = np.zeros([banks,NFFT//2+1])
    for j in range(banks-2):
        for i in range(fft_bins[j], fft_bins[j+1]):
            filter_bank[j,i] = (i - fft_bins[j]) / (fft_bins[j+1]-fft_bins[j])
        for i in range(fft_bins[j+1], fft_bins[j+2]):
            filter_bank[j,i] = (fft_bins[j+2]-i) / (fft_bins[j+2]-fft_bins[j+1])
    features = np.dot(fft,filter_bank.T)
    feat = np.where(features == 0,np.finfo(float).eps,features)
    feat = np.log(feat)
    return sp.dct(feat,type=2, norm='ortho')[:numcep]


def get_mfcc_vec(array):
    max_power = 0
    arr =[]
    for index in range(0,len(array),160):
        chunk = array[index:index+400]
        power = sum(map(abs,chunk))
        if power > max_power: max_power = power
        difference = 0
        spec = mel_spectra(chunk)
        nspec = list(map(lambda x: x/max(spec), spec))
        for fpointer in range(1,len(chunk)):
            difference += abs(chunk[fpointer-1]-chunk[fpointer])
        if power != 0:
            arr.append([power,difference/power,*nspec])
        else:
            arr.append([0]*15)
    
    for i in range(0,len(arr)):
        arr[i][0] = arr[i][0]/(max_power+1e-19)
    return arr


