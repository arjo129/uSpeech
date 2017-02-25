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
#ifdef PICKLE
#include <string.h>
#endif
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#define SILENCE 2000
#define F_DETECTION 3
#define F_CONSTANT 350
#define MAX_PLOSIVETIME 1000
#define PROCESS_SKEWNESS_TIME 15
/**
 *  The main recognizer class
 */
class signal{
public:
	uint16_t arr[32];  /*!< This is the audio buffer*/
	uint16_t avgPower;
	uint16_t testCoeff;
	uint16_t minVolume;  /*!< This is the highest audio power that should be considered ready */
	uint16_t fconstant;  /*!< This is the threshold for /f/, configure it yourself */
	uint16_t econstant;  /*!< This is the threshold for /ee/, /i/, configure it yourself */
	uint16_t aconstant;  /*!< This is the threshold for /a/ /o/ /r/ /l/, configure it yourself */
 	uint16_t vconstant;  /*!< This is the threshold for /z/ /v/ /w/, configure it yourself */
	uint16_t shconstant; /*!< This is the threshold for /sh/ /ch/, above this everything else is regarded as /s/ */
	bool f_enabled; /*!< Set this to false if you do not want to detect /f/s */
	uint16_t amplificationFactor; /*!< Amplification factor: Adjust as you need*/
	uint16_t micPowerThreshold; /*!< Ignore anything with micPower below this */
	uint16_t scale;
	char phoneme;	/*!< The phoneme detected when f was returned */
	signal(uint16_t port);
	uint16_t micPower;
	void sample();
	unsigned uint16_t maxPower();
	unsigned uint16_t power();
	uint16_t snr(uint16_t power);
	void calibrate();
	char getPhoneme();
	uint16_t calib;
private:
	uint16_t pin;
	uint16_t mil;
	uint16_t maxPos;
	bool silence;
	unsigned uint16_t overview[7];
	unsigned uint16_t complexity(uint16_t power);
};
/**
* Considering to delete this if the skewness actually works
*/
class statCollector {
public:
    //Note: May be necessary to change to double type.
    uint16_t n,mean,M2,M3,M4;
    statCollector();
    uint16_t kurtosis();
    uint16_t skew();
    uint16_t _mean();
    uint16_t stdev();
    void collect(uint16_t x);
 
};


/**
 *  Simple Accumulator Vector. Stores simple syllables. Useful for basic word recognition.
 */
class syllable{
public:
    uint16_t f,e,o,s,h,v; /*!< Accumulators for the stated characters */
	uint16_t maxf,maxe,maxo,maxs,maxh,maxv; /*!< These can be used to calculate skewness like this: \frac{1}{2}-\frac{maxs}{length}*/
	uint16_t modalityf, modalitye, modalityo, modalitys, modalityh, modalityv; /*!< These are indicative of whether or not there were two peaks*/
	uint16_t length; /*!< length of utterance */
	uint16_t plosiveCount; /*< Counts the number of plosives*/
    syllable(); /*!< Constructor for the class*/
    void reset(); /*!< Resets the accumulator so a new syllable can be formed. Call this when you detect silence*/
    void classify(char c); 
    uint16_t* tointptr(); /*!< Returns the vector from the accumulators as an integer pointer */
    #if ARDUINO_ENVIRONMENT > 0 
    void debugPrint(); /*!< Outputs the datain the accumulator vector. Only enabled for arduino.*/
	void distance(syllable s);
	
    #endif
    #ifdef PICKLE
    	void dePickle(char* string);
    	char* Pickle();
    #endif
private:
	char cf,ce,co,cs,ch,cv; /*!< Temporary accumulators */
	char prevf,preve,prevo,prevs,prevh, prevv; /*!< Temporary accumulators */
	char currPeak, expectSp;
	unsigned long lastTime;
};
//TODO: implement statistics classes.

#endif
