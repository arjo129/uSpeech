#include "uspeech.h"

signal::signal(int port){
	int pin = port;
}
void signal::calibrate(){
	calib = (analogRead(pin)+analogRead(pin)+analogRead(pin)+analogRead(pin))/4;
}
void signal::sample(){
	int i = 0;
	while ( i < 32){
		arr[i] = analogRead(pin)-calib;	
		i++;
	}
	
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
