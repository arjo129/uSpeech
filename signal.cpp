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
    micPowerThreshold = 50;
    scale = 1;
}
/**
 * Calibration of background based on averaging 
 */
void signal::calibrate(){
#ifdef ARDUINO_ENVIRONMENT 
    calib = 0;
    uint32_t samp=0;
    for (uint16_t ind=0; ind<10000; ind++) {
	//acquire background noise
	samp += analogRead(pin) * scale;
    }
    calib = samp/10000;
#endif
}
/**
 * Sampling of the sound: Based on storing values minus average background noise
 */
void signal::sample(){
	int i = 0;
	while ( i < 32){
#ifdef ARDUINO_ENVIRONMENT
		arr[i] = (analogRead(pin)*scale-calib);
#endif
		i++;
	}
	
}
/**
 * An estimate of background noise
 */
unsigned int signal::power(){
	unsigned int j = 0;
	uint8_t i = 0;
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
	uint8_t i = 1;
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
unsigned int signal::maxPower()
{
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
	uint8_t i=0,j=0;
	int mean =power/32;
	while(i <32){
		j+=sq(arr[i]-mean);
		i++;
	}
	return sqrt(j/mean)/power;
}
