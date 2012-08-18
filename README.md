# uSpeech library #
The uSpeech library provides an interface for voice recognition using the Arduino. It currently produces phonemes, often the library will produce junk phonemes. Please bare with it for the time being. A noise removal function is underway.
##Minimum Requirements ##
The library is quite intensive on the processor. Each sample collection takes about 3.2 milliseconds so pay close attention to the time. The library has been tested on the Arduino Uno. Each signal object uses up 160bytes. No real time scheduler should be used with this.

## Features ##
 - Letter based recognition
 - Small memory footprint
 - Arduino Compatible
 - No training required
 - Fixed point arithmetic


## Documentation ##
Documentation on this library is a work in progress. The GitHub wiki will have more on the library. 