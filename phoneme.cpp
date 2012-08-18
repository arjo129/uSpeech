#include "uspeech.h"

char signal::getPhoneme(){
	sample();
	char t;
	int pow = power();
	int icomplexity = complexity(pow);
	if(pow>SILENCE){
		if(icomplexity>40){
			//voice.voiceFormants();
			mil++;
			//Serial.println(icomplexity);
			if(icomplexity>50){
				if(icomplexity>60){
					if(icomplexity>70){
						if(icomplexity>80){
							if(mil>5){
								t = 's';
							}
							else{
								t = 'k';
							}
						}
						else{
							t = 'z';
						}
					}
					else{
						if(mil>5){
							t = 'z';
						}
						else{
							t = 'g';
						}
					}
				}
				else{
					if(mil>5){
						t = 'v';
					}
					else{
						t = 'p';
					}
				}
			}
			else{
				if(mil>5){
					t = 'v';
				}
				else{
					t = 'p';
				}
			}
			
		}
		else{
			//Perform Formant analysis
			//Serial.println("vowel");
			voiceFormants();
			formantAnal();
			if(formants[3]<8){
				t = 'r';
			}
			if(formants[0]==1){
				if(formants[1]>=9&&formants[1]<=11){
					t = 'e';
				}
				else{
					t = 'o';
				}
			}
			else{
				if(formants[0] == 0){
					if(formants[1]>=13 && formants[1]<=16){
						t = 'i';
					}
					else{
						t = 'o';
					}
				}
				else {
					t = 'a';
				}
			}
			mil =0;

		}
	}
	else{
		t = 'h';
	}
	return t;
}
void signal::formantAnal(){
	int i = 0;
	int k = 0;
	while(i<18){
		if((long)(filters[i]-filters[i-1]) > 0 & (long)(filters[i]-filters[i+1]) < 0){
			if(k < 3){
				formants[k] = i;
			}
		}
		i++;
	}
}