/*
 uspeech v.4.x.x
 2012 Arjo Chakravarty
 
 uspeech is a library that allows sounds to be classified into certain phonemes
 on the Arduino. This creates a simple beginning for a full scale voice recognition
 program.
 */
#ifndef uspeech_h
#define uspeech_h

#define ARDUINO_ENVIRONMENT 1
#if ARDUINO_ENVIRONMENT > 0
    #include "Arduino.h"
#endif

#include <math.h>
#include <stdlib.h>
#define SILENCE 2000
#define F_DETECTION 3
#define F_CONSTANT 350

class signal{
public:
	int arr[32];  /*!< This is the audio buffer*/
    int avgPower;
    int testCoeff;
    int minVolume;  /*!< This is the highest audio power that should be considered ready */
    int fconstant;  /*!< This is the threshold for /f/, configure it yourself */
    int econstant;  /*!< This is the threshold for /ee/, /i/, configure it yourself */
    int aconstant;  /*!< This is the threshold for /a/ /o/ /r/ /l/, configure it yourself */
    int vconstant;  /*!< This is the threshold for /z/ /v/ /w/, configure it yourself */
    int shconstant; /*!< This is the threshold for /sh/ /ch/, above this everything else is regarded as /s/ */
    bool f_enabled; /*!< Set this to false if you do not want to detect /f/s */
	int amplificationFactor; /*!<Amplification factor: Adjust as you need*/
    signal(int port);
    int micPower;
	void sample();
    unsigned int maxPower();
	unsigned int power();
	unsigned int complexity(int power);
	int snr(int power);
	void calibrate();
	
	char getPhoneme();
    
    
private:
	int goertzel(int freq); //remove
	int pin;
	int mil;
    int maxPos;
	bool silence;
    int calib;
    unsigned int overview[7];
    
};

class syllable{
public:
    int f,e,o,s,h,v;
    syllable();
    void classify(char c);
    int* tointptr();
    #if ARDUINO_ENVIRONMENT > 0
    void debugPrint();
    #endif
    
};

#endif
