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
private:
	int pin;
	int mil;
	bool silence;
	void formantAnal();
};

bool IsVowel(char c);
bool uIsVowel(char c);
bool uIsPlosive(char c);
bool in(char c, String s);
int umatch(String ing, String desired);
int getSyllables(String ing);
int mapChar(char a);
int subChar(char a, char b);
String denoise(char c, String prev);
#endif