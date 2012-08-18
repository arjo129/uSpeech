#include "uspeech.h"

signal::signal(int port){
	int pin = port;
}
void signal::calibrate(){
	calib = (analogRead(pin)+analogRead(pin)+analogRead(pin)+analogRead(pin))/4;
}
void signal::sample(){
	arr[0] = analogRead(pin)-calib;
	arr[1] = analogRead(pin)-calib;
	arr[2] = analogRead(pin)-calib;
	arr[3] = analogRead(pin)-calib;
	arr[4] = analogRead(pin)-calib;
	arr[5] = analogRead(pin)-calib;
	arr[6] = analogRead(pin)-calib;
	arr[7] = analogRead(pin)-calib;
	arr[8] = analogRead(pin)-calib;
	arr[9] = analogRead(pin)-calib;
	arr[10] = analogRead(pin)-calib;
	arr[11] = analogRead(pin)-calib;
	arr[12] = analogRead(pin)-calib;
	arr[13] = analogRead(pin)-calib;
	arr[14] = analogRead(pin)-calib;
	arr[15] = analogRead(pin)-calib;
	arr[16] = analogRead(pin)-calib;
	arr[17] = analogRead(pin)-calib;
	arr[18] = analogRead(pin)-calib;
	arr[19] = analogRead(pin)-calib;
	arr[20] = analogRead(pin)-calib;
	arr[21] = analogRead(pin)-calib;
	arr[22] = analogRead(pin)-calib;
	arr[23] = analogRead(pin)-calib;
	arr[24] = analogRead(pin)-calib;
	arr[25] = analogRead(pin)-calib;
	arr[26] = analogRead(pin)-calib;
	arr[27] = analogRead(pin)-calib;
	arr[28] = analogRead(pin)-calib;
	arr[29] = analogRead(pin)-calib;
	arr[30] = analogRead(pin)-calib;
	arr[31] = analogRead(pin)-calib;
}
unsigned int signal::power(){
	unsigned int j = 0;
	char i = 0;
	while(i<32){
	
		j+=abs(arr[i]);
		i++;
	}
	return j;
}
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
int signal::snr(int power){
	int i =0,j=0;
	int mean =power/32;
	while(i <32){
		j+=sq(arr[i]-mean);
		i++;
	}
	return sqrt(j/mean)/power;
}
