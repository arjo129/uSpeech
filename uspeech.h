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

class signal{
public:
	int arr[32];
	int calib;
	signal(int port);
	void sample();
	unsigned int power();
	unsigned int complexity(int power);
	unsigned long fpowerex(int sum, int xtra);
	int snr(int power);
	void calibrate();
	unsigned long filters[18], formants[3], intoned;
	char getPhoneme();
	void debugPrintFilter();
	void voiceFormants();
	int goertzel(int freq);
private:
	int pin;
	int mil;
	bool silence;
	void formantAnal();
};
//With the emminent release of Arduino Due, it makes no sense to not include
//an fft based algorythm
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