/*
 uspeech v.1.9.2 (2.0betaRC1)
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
#define F_DETECTION 0
class signal{
public:
	int arr[32];
	int calib;
	signal(int port);
	void sample();
    unsigned int maxPower();
	unsigned int power();
	unsigned int complexity(int power);
	unsigned long fpowerex(int sum, int xtra);
	int snr(int power);
	void calibrate();
	unsigned long filters[18], formants[3], intoned;
	unsigned int overview[7];
	char getPhoneme();
	void debugPrintFilter();
	void voiceFormants();
	int goertzel(int freq);
    unsigned int micPower;
private:
	int pin;
	int mil;
	bool silence;
	void formantAnal();
};


#endif