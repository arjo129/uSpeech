#include "uspeech.h"
/**
 * Constructor 
 */
signal::signal(int port){
	pin = port;
    fconstant = F_CONSTANT;
    econstant = 2;
    aconstant = 4;
    vconstant = 6;
    shconstant = 10;
    amplificationFactor = 10;
}
/**
 * Calibration of background based on averaging 
 */
void signal::calibrate(){
    #ifdef ARDUINO_ENVIRONMENT > 0
	calib = (analogRead(pin)+analogRead(pin)+analogRead(pin)+analogRead(pin))/4; //acquire background noise
    #endif
}
/**
 * Sampling of the sound: Based on storing values minus average background noise
 */
void signal::sample(){
	int i = 0;
	while ( i < 32){
        #ifdef ARDUINO_ENVIRONMENT > 0
		arr[i] = analogRead(pin)-calib;
        #endif
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
    //Serial.println(j);
	return (j*amplificationFactor)/power;
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