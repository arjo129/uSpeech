#include "uspeech.h"
void microphone::processCoeffs(){
	int i;
	//Lower frequencies more important, make them larger
	while(i<5){
		if(dominantfreq[i]!=0){
			dominantfreq[i] = 128 - dominantfreq[i];
		}
		i++;
	}
	int d[5];
	d[0]=0;d[1]=0;d[2]=0;d[3]=0;d[4]=0;
	//re-order them, lowest frequencies first
	i =0;
	while(i<5){
		int j = 0;
		while(j<(5-i)){
			float swap,swap2;
			if(dominantfreq[j]<dominantfreq[j-1]){
				swap = dominantfreq[j];
				swap2 = dominantfreq[j-1];
				dominantfreq[j-1] = swap;
				dominantfreq[j] = swap2;
			}
			j++;
		}
		i++;
	}
}