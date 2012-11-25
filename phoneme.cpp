#include "uspeech.h"

char signal::getPhoneme(){
	sample();
	if(power()>SILENCE){
		coeff = complexity(power());
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