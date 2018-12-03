# uSpeech library #
This branch is a rewrite in progress of the original uSpeech algorithm. Given advances in deep learning it should now be possible
to use these advances to generate a model. As such, this branch is no longer going to be written in C++. Rather,
this branch will utilize python to generate a C++ library which can be embedded for any given board. As of now this a a massive work in progress.

## What has been done ##
It is now possible to use tensorflow to train a tiny model based on GRUs that utilizes the uspeech library's feature recognition APIs to
perform simple speech recognition. In particular, a few things were explored. Initially using a vector consisting of
`[power, uspeech_coeff]` was attempted. This only achieved recognition accuracy of barely above 60% in a 4 word task. In contrast using MFCCs gave an accuracy of 86% (which is kind of disappointing). Normallizing power seemed to work rather well and the test accuracy of the
data set reached 97%. However, normallizing power on an MCU is expensive as it will require storing the whole utterance in memory. So next I tried to use the ratio between pwer of the previous sample and power of the current sample. The purpose was to clamp the values close to 1 so that the GRU is not overwhelmed. This did not work as there were times when large energy bursts occured the value of the ratio would still far exceed 1. Thus, I placed an upper bound of 1.5 on this ratio. This brought the test accuracy back up to 86%.

## What needs to be done ##
[ ] Read words from CMUDict and use them to perform phoneme based classification
[ ] Implement CTC
[ ] Implement CodeGen
[ ] Standardise API
[ ] Write docs
[ ] Write unit tests
[ ] Setup CI