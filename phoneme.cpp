#include "uspeech.h"
/**
* The recognizer function: takes 1-4ms to execute
*/
char signal::getPhoneme(){
#if ARDUINO_ENVIRONMENT > 0
	sample();
#endif
    unsigned int pp =power();
	if(pp>SILENCE){
        
		//Perform Division
		int k = complexity(pp);
        //Low pass filter for noise removal
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
        testCoeff = coeff;
		//Serial.println(coeff); //Use this for debugging
        if(f_enabled){
            micPower = 0.05 * maxPower() + (1 - 0.05) * micPower;
            //Serial.println(micPower)//If you are having trouble with fs
            if (micPower > fconstant) {
                return 'f';
            }
        }

	//Twiddle with the numbers here if your getting false triggers
	//This is the main classifier part
	
        if(coeff<econstant /*Default value = 2*/){
				return 'e';
			}
			else{
				if(coeff<aconstant /*Default value = 4*/){
					return 'o';
				}
				else{
					if(coeff<vconstant /*Default value = 6*/){
						return 'v';
					}
					else{
						if(coeff<shconstant /*Default value = 10*/){
							return 'h';
						}
						else{
							if(coeff>shconstant){
								return 's';
							}
							
						}
					}
				}
			}
		
	}
	else{
        micPower = 0;
       
        testCoeff = 0;
		return ' ';
	}
}

