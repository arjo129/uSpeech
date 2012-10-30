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

//Updated more accurate & easier to use class
//Memory footprint increased however will continue running on Arduino UNO
class microphone {
public:
	microphone::microphone(int pin); //Microphone class initialization
	void sample();//Microphone sampling, loads stuff into buffer
	unsigned int complexity(); // Good old complexity function
	void calibarate(); //used to calibrate microphone
	char match(); //get a phoneme
	
private:
	char data[128]; //The buffer containing raw data/fft of data
	char dominantfreq[5]; //Extracted "fingerprint"
	int calib; //
	int port; //the analog in port of the microphone
	void extractCoefficients(); //The coefficients act as finger prints
};



//Taken from the 8bit FFT on the arduino Forums. See FFT.cpp fo
//Full credit
/*
 fix_fft() - perform forward/inverse fast Fourier transform.
 fr[n],fi[n] are real and imaginary arrays, both INPUT AND
 RESULT (in-place FFT), with 0 <= n < 2**m; set inverse to
 0 for forward transform (FFT), or 1 for iFFT.
 */
int fix_fft(char fr[], char fi[], int m, int inverse);



/*
 fix_fftr() - forward/inverse FFT on array of real numbers.
 Real FFT/iFFT using half-size complex FFT by distributing
 even/odd samples into real/imaginary arrays respectively.
 In order to save data space (i.e. to avoid two arrays, one
 for real, one for imaginary samples), we proceed in the
 following two steps: a) samples are rearranged in the real
 array so that all even samples are in places 0-(N/2-1) and
 all imaginary samples in places (N/2)-(N-1), and b) fix_fft
 is called with fr and fi pointing to index 0 and index N/2
 respectively in the original array. The above guarantees
 that fix_fft "sees" consecutive real samples as alternating
 real and imaginary samples in the complex array.
 */
int fix_fftr(char f[], int m, int inverse);

#endif