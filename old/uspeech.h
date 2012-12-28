/*
uspeech v.0.0.1
2012 Arjo Chakravarty

uspeech is a library that allows sounds to be classified into certain phonetics
on the Arduino. This creates a simple beginning for a full scale voice recognition
program
*/
#ifndef uspeech_h
#define uspeech_h

#include "Arduino.h"
#define SAMPLEWINDOW 64


class uspeech
{
  public:
    uspeech(int pin);
    void classify();
	void calibrate();
	float loudness();
	bool isIntoned();
	bool isReady();
	float getVXCoeff();
	float THRESHOLD;
  private:
	//void push();
	float mvAvg;
	float nt;
	float sum;
	int sensorPin;    
	float calib;      
	float sensorValue;  // variable to store the value coming from the sensor
	float prev;
	float prev2;
	bool state;
	bool haveread;
	int iter;
	unsigned int dif;
};

#endif