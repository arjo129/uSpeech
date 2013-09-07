#include "uspeech.h"
/**
 * Constructor 
 */
signal::signal(int port){
	int pin = port;
}
/**
 * Calibration of background based on averaging 
 */
void signal::calibrate(){
	calib = (analogRead(pin)+analogRead(pin)+analogRead(pin)+analogRead(pin))/4; //acquire background noise
}
/**
 * Sampling of the sound: Based on storing values minus average background noise
 */
void signal::sample(){
	int i = 0;
	while ( i < 32){
		arr[i] = analogRead(pin)-calib;	
		i++;
	}
	
}
/**
 * An estimate of background noise
 */
unsigned int signal::power(){
	unsigned int j = 0;
	char i = 0;
	while(i<32){
	
		j+=abs(arr[i]);
		i++;
	}
	return j;
}
/**
 * power/abs(sum of derivative)
 */
unsigned int signal::complexity(int power){
	unsigned int j = 0;
	int i = 1;
	while(i<32){
		j+=abs(arr[i]-arr[i-1]);
		i++;
	}
	return (j*100)/power;
}

unsigned long signal::fpowerex(int sum, int xtra){
	
	int i = sum;
	unsigned long j = abs(arr[i-1]*(xtra/10));
	int p;
	while(i<32){
		int k = 0;
		p = 0;
		while(k<sum){
			p+=abs(arr[i-k]);
			k++;
		}
		j+=p/sum+p/(xtra/10);
		i++;
		//Serial.println(j);
	}
	return j;
}
/**
* Point of maximum amplitude
*/
unsigned int signal::maxPower(){
    int i =0;
    unsigned int max = 0;
    while (i<32){
        if(max<abs(arr[i])){
            max = abs(arr[i]);
            maxPos = i;
        }
        i++;
        avgPower+=arr[i];
    }
    avgPower /= 32;
    return max;
}
int signal::snr(int power){
	int i =0,j=0;
	int mean =power/32;
	while(i <32){
		j+=sq(arr[i]-mean);
		i++;
	}
	return sqrt(j/mean)/power;
}
void signal::zeroCrossingSearch(){
	int i=maxPos;
	int prev = arr[i];
	int upper = 0;
	int lower = 0;
	while (i<32){
		prev = arr[i]-avgPower;
		if(prev<0){
			upper = i;
			i = 33; //Break out of loop
		}
		i++;
	}
	i=maxPos;
	while (i>0){
		prev = arr[i]-avgPower;
		if(prev<0){
			lower = i;
			i = 0; //Break out of loop
		}
		i--;
	}
	vowelRatio = (upper-i)*100/lower-i;
}
