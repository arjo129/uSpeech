/*
 uspeech v.0.0.1
 2012 Arjo Chakravarty
 
 uspeech is a library that allows sounds to be classified into certain phonemes
 on the Arduino. This creates a simple beginning for a full scale voice recognition
 program.
 */
#ifndef uspeech_h
#define uspeech_h

#include "Arduino.h"
#include <math.h>
#define SILENCE 92

//Updated more accurate & easier to use class
//Memory footprint increased however will continue running on Arduino UNO
class microphone {
public:
	microphone::microphone(int pin);
	void sample();
	unsigned int complexity();
	void calibarate();
	char match();
private:
	char data[128];
	char calib;
	int port;
};


#endif