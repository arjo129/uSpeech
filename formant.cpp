#include "uspeech.h"

void signal::voiceFormants(){
	unsigned int j;
	filters[0] = fpowerex(25,0); //400
	j+= filters[0];
	filters[1] = fpowerex(16,6)-j; //600
	j+= filters[1];
	filters[2] = fpowerex(12,5)-j; //800
	j+= filters[2];
	filters[3] = fpowerex(10,0)-j; //1000
	j+= filters[3];
	filters[4] = fpowerex(8,3)-j; //1200
	j+= filters[4];
	filters[5] = fpowerex(7,1)-j; //1400
	j+= filters[5];
	filters[6] = fpowerex(6,3)-j; //1600
	j+= filters[6];
	filters[7] = fpowerex(5,5)-j; //1800
	j+= filters[7];
	filters[8] = fpowerex(5,0)-j; //2000
	j+= filters[8];
	filters[9] = fpowerex(4,5)-j; //2200
	j+= filters[9];
	filters[10] = fpowerex(4,0)-j; //2400
	j+= filters[10];
	filters[11] = fpowerex(3,8)-j; //2600
	j+= filters[11];
	filters[12] = fpowerex(3,5)-j; //2800
	j+= filters[12];
	filters[13] = fpowerex(3,3)-j; //3000
	j+= filters[13];
	filters[14] = fpowerex(2,9)-j; //3200
	j+= filters[14];
	filters[15] = fpowerex(2,7)-j; //3400
	j+= filters[15];
	filters[16] = fpowerex(2,6)-j; //3600
	j+= filters[16];
	filters[17] = fpowerex(2,5)-j; //3800
	j+= filters[17];
}
void signal::debugPrintFilter(){
	int i = 0;
	while(i<18){
		Serial.println(filters[i]);
		i++;
	}
	Serial.println("-----");
}

int signal::goertzel(int freq){
freq =  freq/100000;
int s_prev = 0 ;
int s_prev2 = 0 ;
int coeff = 2 * cos(2 * 3.14 * freq) ;
for(int i = 2; i < 32; i++){
	int s = arr[i] + coeff *s_prev  - s_prev2 ;
	s_prev2 = s_prev ;
	s_prev = s ;
}
return s_prev2 * s_prev2 + s_prev * s_prev - coeff * s_prev * s_prev2 ;

}
