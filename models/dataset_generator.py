import os
import re
import hashlib
import random
from wavfile_decoder import *
interested_words = 'yes no up down left right stop go unknown'.split()


def pad_batch(array,vec_size=2):
    maximum_len = max(map(len,array))
    for item in range(0,len(array)):
        if len(array[item]) < maximum_len:
            array[item].extend([[0]*vec_size]*(maximum_len-len(array[item])))
        array[item] = np.array(array[item])

def get_silence():
    word = "_background_"
    filename = random.choice(os.listdir("_background_/"))
    arr = wav2arr("_background_/"+filename)
    length = len(arr) - 1600
    start = random.randint(0,length)
    return arr[start:start+1600]

def get_batch(dataset, batchsize=32, batchtype="train"):
    X = []
    Y = []
    for i in range(batchsize):
        word = random.choice(interested_words) 
        if word != "unknown" and word !="_background_":
            filename = random.choice(dataset[word][batchtype])
            X.append(get_uspeech_vec(wav2arr(word+"/"+filename)))
        elif word == "_background_":
            X.append(get_uspeech_vec(get_silence()))
        else:
            filename = random.choice(dataset[word][batchtype])
            X.append(get_uspeech_vec(wav2arr(filename)))
        output = [0]*len(interested_words)
        output[interested_words.index(word)] = 1
        Y.append(output)
    pad_batch(X)
    X = np.array(X)
    Y = np.array(Y)
    return X,Y
        
def get_smallest_class(dataset):
    min = float('inf')
    minkey = ""
    for word in dataset.keys():
        if len(dataset[word]["train"])<min:
            min = len(dataset[word]["train"])
            minkey = word
    return minkey

def build_dataset():
    data_set = {"unknown":{"train":[],"validate":[],"test":[]}}
    words = get_word_list()
    for word in words:
        test,valid,train = generate_class_split(word)
        if word in interested_words:
            data_set[word] = {"train":train,"validate":valid,"test":test}
        else:
            data_set["unknown"]["train"].extend(list(map(lambda x: word+"/"+x , train)))
            data_set["unknown"]["validate"].extend(list(map(lambda x: word+"/"+x , valid)))
            data_set["unknown"]["test"].extend(list(map(lambda x: word+"/"+x , test)))
    return data_set

def get_word_list():
    return filter(lambda file: file[0]!="_" and os.path.isdir(file),os.listdir())

def get_files_in_class(word):
    return os.listdir(word)

def generate_class_split(word, validation_percentage = 10, testing_percentage = 20):
    testing = []
    validation = []
    training = []
    for filename in get_files_in_class(word):
        _set = which_set(filename,validation_percentage, testing_percentage)
        if _set == "validation":
            validation.append(filename)
        elif _set == "testing":
            testing.append(filename)
        else:
            training.append(filename)
    return testing,validation,training

MAX_NUM_WAVS_PER_CLASS = 2**27 - 1  # ~134M

def which_set(filename, validation_percentage, testing_percentage):
  """Determines which data partition the file should belong to.

  We want to keep files in the same training, validation, or testing sets even
  if new ones are added over time. This makes it less likely that testing
  samples will accidentally be reused in training when long runs are restarted
  for example. To keep this stability, a hash of the filename is taken and used
  to determine which set it should belong to. This determination only depends on
  the name and the set proportions, so it won't change as other files are added.

  It's also useful to associate particular files as related (for example words
  spoken by the same person), so anything after '_nohash_' in a filename is
  ignored for set determination. This ensures that 'bobby_nohash_0.wav' and
  'bobby_nohash_1.wav' are always in the same set, for example.

  Args:
    filename: File path of the data sample.
    validation_percentage: How much of the data set to use for validation.
    testing_percentage: How much of the data set to use for testing.

  Returns:
    String, one of 'training', 'validation', or 'testing'.
  """
  base_name = os.path.basename(filename)
  # We want to ignore anything after '_nohash_' in the file name when
  # deciding which set to put a wav in, so the data set creator has a way of
  # grouping wavs that are close variations of each other.
  hash_name = re.sub(r'_nohash_.*$', '', base_name)
  # This looks a bit magical, but we need to decide whether this file should
  # go into the training, testing, or validation sets, and we want to keep
  # existing files in the same set even if more files are subsequently
  # added.
  # To do that, we need a stable way of deciding based on just the file name
  # itself, so we do a hash of that and then use that to generate a
  # probability value that we use to assign it.
  hash_name_hashed = hashlib.sha1(str(hash_name).encode('utf-8')).hexdigest()
  percentage_hash = ((int(hash_name_hashed, 16) %
                      (MAX_NUM_WAVS_PER_CLASS + 1)) *
                     (100.0 / MAX_NUM_WAVS_PER_CLASS))
  if percentage_hash < validation_percentage:
    result = 'validation'
  elif percentage_hash < (testing_percentage + validation_percentage):
    result = 'testing'
  else:
    result = 'training'
  return result

#print(build_dataset()["unknown"])
