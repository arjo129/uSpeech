#include "uspeech.h"

char signal::getPhoneme(){
	sample();
	if(power()>SILENCE){
		int k = complexity(power()); 
		overview[6] = overview[5];
		overview[5] = overview[4];
		overview[4] = overview[3];
		overview[3] = overview[2];
		overview[2] = overview[1];
		overview[1] = overview[0];
		overview[0] = k;
		int coeff = 0;
		char f = 0;
		while(f<6){
			coeff += overview[f];
			f++;
		}
		coeff /= 7;
        micPower = 5 * maxPower() + (100 - 5) * micPower;
        if (micPower>95) {
            return 'f';
        }
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
						return 'v';
					}
					else{
						if(80>coeff>70){
							return 'h';
						}
						else{
							if(coeff>80){
								return 's';
							}
							else{
								return 'm';
							}
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