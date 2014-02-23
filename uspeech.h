/*
 uspeech v.4.x.x
 2012-2014 Arjo Chakravarty
 
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

/**
 *  The main recognizer class
 */
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
	int micPowerThreshold; /*!< Ignore anything with micPower below this */
	int scale;
	char phoneme;	/*!< The phoneme detected when f was returned */
	signal(int port);
	int micPower;
	void sample();
	unsigned int maxPower();
	unsigned int power();
	int snr(int power);
	void calibrate();
	char getPhoneme();
	int calib;
private:
	int pin;
	int mil;
	int maxPos;
	bool silence;
	unsigned int overview[7];
	unsigned int complexity(int power);
};

class statCollector {
public:
    //Note: May be necessary to change to double type.
    int n,mean,M2,M3,M4;
    statCollector();
    int kurtosis();
    int skew();
    int _mean();
    int stdev();
    void collect(int x);
 
};


/**
 *  Simple Accumulator Vector. Stores simple syllables. Useful for basic word recognition.
 */
class syllable{
public:
    int f,e,o,s,h,v; /*!< Accumulators for the stated characters */
    syllable(); /*!< Constructor for the class*/
    void reset(); /*!< Resets the accumulator so a new syllable can be formed. Call this when you detect silence*/
    void classify(char c); 
    int* tointptr(); /*!< Returns the vector from the accumulators as an integer pointer */
    #if ARDUINO_ENVIRONMENT > 0 
    void debugPrint(); /*!< Outputs the datain the accumulator vector. Only enabled for arduino.*/
    #endif
};
//TODO: implement statistics classes.
#endif
