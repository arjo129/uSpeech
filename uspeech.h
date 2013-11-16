/*
 uspeech v.3.0Alpha
 uspeech v.4.0.1Alpha
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
    int minVolume;  /*!< This is the highest audio power that should be considered ready */
    int fconstant;  /*!< This is the threshold for /f/, configure it yourself */
    int econstant;  /*!< This is the threshold for /ee/, /i/, configure it yourself */
    int aconstant;  /*!< This is the threshold for /a/ /o/ /r/ /l/, configure it yourself */
    int vconstant;  /*!< This is the threshold for /z/ /v/ /w/, configure it yourself */
    int shconstant; /*!< This is the threshold for /sh/ /ch/, above this everything else is regarded as /s/ */
    BOOL f_enabled; /*!< Set this to false if you do not want to detect /f/s */
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