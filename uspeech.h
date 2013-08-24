/*
 uspeech v.3.0Alpha
 2012 Arjo Chakravarty
 
 uspeech is a library that allows sounds to be classified into certain phonemes
 on the Arduino. This creates a simple beginning for a full scale voice recognition
 program.
 */
#ifndef uspeech_h
#define uspeech_h

#include "Arduino.h"
#include <math.h>
#define SILENCE 1500
#define F_DETECTION 3
#define F_CONSTANT 380
class signal{
public:
	int arr[32],avgPower;
	int calib;
    int testCoeff;
	signal(int port);
    int micPower;
	void sample();
    unsigned int maxPower();
	unsigned int power();
	unsigned int complexity(int power);
	unsigned long fpowerex(int sum, int xtra); //Todo: Remove
	int snr(int power);
	void calibrate();
	unsigned int overview[7];
	char getPhoneme(); //void lowPass(int freq); Todo: Implement moving average low pass filter.
    int goertzel(int freq);
    int vowelRatio;
    void zeroCrossingSearch();
private:
	int pin;
	int mil;
    int maxPos;
	bool silence;
	void formantAnal(); //Todo: Remove
    
};


#endif