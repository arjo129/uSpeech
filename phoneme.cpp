#include "uspeech.h"
/**
* The recognizer function: takes 1-4ms to execute
*/
char signal::getPhoneme()
{
#ifdef ARDUINO_ENVIRONMENT
    sample();
#endif
    unsigned int pp =power();
    //Serial.print(F("pp=")); Serial.println(pp);
    if (pp>SILENCE) {
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
	for (uint8_t f=0; f<6; f++) {
	    coeff += overview[f];
	}
	coeff /= 7;

	micPower = 0.05 * maxPower() + (1 - 0.05) * micPower;
	if (micPower < micPowerThreshold) {
	    return ' ';
	}

	testCoeff = coeff;
	//Serial.print(F("coeff: ")); Serial.println(coeff); //Use this for debugging

	//Twiddle with the numbers here if your getting false triggers
	//This is the main classifier part

	if (coeff<econstant) { /*Default value = 2*/
	    phoneme = 'e';
	} else if (coeff<aconstant) { /*Default value = 4*/
	    phoneme = 'o';
	} else if (coeff<vconstant) { /*Default value = 6*/
	    phoneme = 'v';
	} else if (coeff<shconstant) { /*Default value = 10*/
	    phoneme = 'h';
	} else {
	    phoneme = 's';
	}

	if (f_enabled) {
	    //Serial.print(F("micPower: ")); Serial.println(micPower);
	    if (micPower > fconstant) {
		return 'f';
	    }
	}

	return phoneme;

    }

    micPower = 0;
    testCoeff = 0;
    return ' ';
}

