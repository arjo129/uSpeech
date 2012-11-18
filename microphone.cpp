#include "uspeech.h"
/*<c> Arjo Chakravart MIT License
 *
 *This file contains The core functions of the library
 */
microphone::microphone(int pin){
	port = pin;
}
void microphone::sample(){
	//Serial.println("Called sample()");
	
	int i = 0;
	while(i < 128){
		int k =(analogRead(port))-calib;
		if(abs(k)>=128){
		}
		else{
			data[i] = k;
			//Serial.println(k);
		}
		i++;
	}
	//Serial.println("Sample completed");
}
/* This is the complexity function
 * 
 * 1. Take the absolute sum of all the values					[done]
 * 2. Get the sum of the differential of all values				[done]
 * 3. Get the difference over the power in a fixed point form	[done]
 */
unsigned int microphone::complexity(){
	int power=0, diff=0;
	char i = 1;
	while(i < 128){
		power += abs((int)data[i]);
		diff += abs((int)(data[i]-data[i-1]));
		i++;
	}
	return (diff*100)/power;
}
void microphone::calibrate(){
	calib = (analogRead(port)+analogRead(port)+analogRead(port)+analogRead(port))/4;
}
/* This is the matching function
 *
 * 1. Take the FFT													[done]
 * 2. Determine using complex coeefficient if consonant or vowel	[done]
 * 3. Get the formants/dominant frequencies							[done]
 * 4. Match to fized set of training data							[TODO]
 * 5. Return the vowel												[TODO]
 *	
 *	input: void
 *  output: char phoneme
 */
char microphone::match(){
	if(power()>SILENCE){
		//Step 1
		int co = complexity();
		//Step 2
		fix_fftr(data,7,NULL);
		//Step 3
		if(co>40){ //fricatives
			extractCoefficients(25);
		}
		else{ 
			extractCoefficients(10);
		}
	}
	return 'h';
}
int microphone::power(){
	int power=0;
	int i = 0;
	while(i < 128){
		power += abs((int)data[i]);
		i++;
	}
	return power;
}

