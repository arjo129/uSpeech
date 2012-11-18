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
float microphone::complexity(){
	float power=0, diff=0;
	int i = 1;
	while(i < 128){
		power += abs((int)data[i]);
		diff += abs((int)(data[i]-data[i-1]));
		i++;
	}
	return (float)(diff*100)/power;
}
void microphone::calibrate(){
	calib = (analogRead(port)+analogRead(port)+analogRead(port)+analogRead(port))/4;
}
/* This is the (experimental) matching function
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
		coeff = complexity();
		//Step 2
		fix_fftr(data,7,NULL);
		//Step 3
		if(coeff>50){ //fricatives
			extractCoefficients(25);
			//Serial.println(complexity());
		}
		else{ 
			extractCoefficients(10);
			//Serial.println(complexity());
		}
	}
	return 'h';
}
/* This is the (old)matching function
 *	1 - Get coefficient [done]
 *  2 - Match			[done]
 *	
 *	input: void
 *  output: char phoneme
 */
char microphone::oldMatch(){
	if(power()>SILENCE){
		coeff = complexity();
		if(coeff<30 && coeff>20){
			return 'u';
		}
		else {
			if(coeff<33&&coeff>25){
				return 'e';
			}
			else{
				if(coeff<46&&coeff>33){
					return 'o';
				}
				else{
					if(coeff>50&&coeff<65){
						return 'a';
					}
					else{
						if(coeff>70){
							return 'h';
						}
						else{
							if(coeff>90){
								return 's';
							}
							return 'm';
						}
					}
				}
			}
		}
	}
	else{
		return ' ';
	}
}
/*A third matching function
 *
 *	Uses the 1st 6 FFT values : stored in dominantfreq[0-3]
 *
 *	matches to formants...
 *
 *	char = vowel;
 */
/*
char microphone::match3(){
	fix_fftr(data,7,NULL);
	dominantfreq[0] = abs(data[0]);
	dominantfreq[1] = abs(data[1]);
	dominantfreq[2] = abs(data[2]);
	dominantfreq[3] = abs(data[3]);
	dominantfreq[4] = abs(data[4]);
	
}*/

int microphone::power(){
	int power=0;
	int i = 0;
	while(i < 128){
		power += abs((int)data[i]);
		i++;
	}
	return power;
}

