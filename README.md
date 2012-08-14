# uSpeech library #
The uSpeech library provides an interface for voice recognition using the Arduino. It currently produces vectors corresponding to the phoneme.
*THE LIBRARY IS UNDERDEVELOPMENT AND UNDERGOING MASSIVE CHANGES I DO NOT ADVICE USE UNTIL A STABLE RELEASE IS OUT*
##Minimum Requirements ##
The library is quite intensive on the processor. Each sample collection takes about 3.2 milliseconds so pay close attention to the time. The library has been tested on the Arduino Uno.

## How to use ##
It takes some effort for making the library recognize speech. Firstly one needs a microphone with a preamplifier. The tested preamplifier used about 100-1000 times amplification. Secondly the library needs to "learn" the different phonemes. A tool is currently under development for this however at present this has to be done manually. More information is available on the wiki. The simplest speech recognizer looks like this:

	
	#include <uspeech.h>
	uspeech recognizer(A0);
	void setup(){
  		Serial.begin(9600);
  		recognizer.calibrate();
	}
	void loop(){
  		phoneme p= recognizer.get();
  		if(p.loudness()>2){
    		p.debugPrint();
  		}
	}

``p.debugPrint()`` displays a vector in the serial console which corresponds to a phoneme.

## Documentation ##
Documentation on this library is a work in progress. The GitHub wiki will have more on the library. 