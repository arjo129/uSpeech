# uSpeech library #
The uSpeech library provides an interface for voice recognition using the Arduino. It currently produces vectors corresponding to the phoneme.
*THE LIBRARY IS UNDERDEVELOPMENT AND UNDERGOING MASSIVE CHANGES I DO NOT ADVICE USE UNTIL A STABLE RELEASE IS OUT*
## Minimum Requirements ##
The library is quite intensive on the processor. Each sample collection takes about 3.2 milliseconds so pay close attention to the time. The library has been tested on the Arduino Uno. A basic speech recognition sketch takes about 256 bytes. The sketch requires a minimum IDE version of 1.0.

## How to use ##
The library implements a fingerprint extraction that gives each phoneme/word a unique fingerprint. The user will need to implement a lookup function after training the recognizer. A sofware for automatic generation of the look up function is underway.

## Documentation ##
Documentation on this library is a work in progress. The GitHub wiki will have more on the library. 