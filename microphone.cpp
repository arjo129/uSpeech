#include "uspeech.h"
/*<c> Arjo Chakravart MIT License
 *
 *This file contains The core functions of the library
 */
void microphone::sample(){
	char i = 0;
	while(i < 128){
		data[i] = (analogRead())/4-calib/4;
	}
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
	}
	return (diff*100)/power;
}
void microphone::calibarate(){
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
		fix_fftr(data,7,NULL);
		//Step 2
		extractCoefficients();
		//Step 3
		if(complexity>40){ //Vowels & liquids
			/*TODO Matching functions*/
		}
		else{ //Consonants
			
		}
	}
}
int power(){
	int power=0;
	char i = 0;
	while(i < 128){
		power += abs((int)data[i]);
	}
	return power;
}
microphone::microphone(int pin){
	port = pin;
}
