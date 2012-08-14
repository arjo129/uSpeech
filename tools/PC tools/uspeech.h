/*
uspeech v.0.0.1
2012 Arjo Chakravarty

uspeech is a library that allows sounds to be classified into certain phonemes
on the Arduino. This creates a simple beginning for a full scale voice recognition
program.
*/
#ifndef uspeech_h
#define uspeech_h

#include <cstdlib.h>
#include <math.h>
#include <time.h>
#include <list>
class phoneme
{

public:
	phoneme(int v,int v1, int v2, int v3, int v4, int v10, int v11, int v12, int v13, int v14);
	unsigned int vector[2][5];
};



class uword
{
public:
	uword();
	unsigned long len;
	unsigned long vector[2][5];
};

class knueralnet
{
public:
	char outputs;
	char weights[10][10];
	char weights2[10][10];
	knueralnet(char output);
	char classify(uword text);
	char classify(phoneme p);
	void randWeight();
private:
	unsigned long o[10];
};

#endif