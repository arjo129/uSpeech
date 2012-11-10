#include "uspeech.h"
/*<c> Arjo Chakravarty MIT License
 *This file contains the peak detection and sorting functions
 */


/** Extract coefficients
 *  Finds the dominant frequencies of a microphone 
 *	1 - Takes the FFT and finds peaks	[done]
 *  2 - Finds the top 5 peaks			[done]
 *	3 - Records their frequencies		[done]
 *  
 *  
 *	Status: Testing complete but function freezes
 *  Input: none
 *	Return: none
 */
void microphone::extractCoefficients(){
	char dominantfreqp[5];
	int i =1;
	dominantfreqp[0] = 0;
	dominantfreqp[1] = 0;
	dominantfreqp[2] = 0;
	dominantfreqp[3] = 0;
	dominantfreqp[4] = 0;
	while(i<25){
		if(data[i-1]<data[i]&&data[i]>data[i-1]){
			if(dominantfreqp[0]<data[i]){
				dominantfreq[0]= (float)i+(((float)(data[i-1]-data[i+1]))/((float)(data[i-1]-2*data[i]+data[i+1])))/2;
				
				dominantfreqp[0] =data[i];
			}
			else{ 
				if (dominantfreqp[1]<data[i]) {
					dominantfreq[1] = (float)i+(((float)(data[i-1]-data[i+1]))/((float)(data[i-1]-2*data[i]+data[i+1])))/2;
					dominantfreqp[1] =data[i];
				}
				else{
					if (dominantfreqp[2]<data[i]) {
						dominantfreq[2] = (float)i+(((float)(data[i-1]-data[i+1]))/((float)(data[i-1]-2*data[i]+data[i+1])))/2;
						dominantfreqp[2] =data[i];
					}
					else{
						if (dominantfreqp[3]<data[i]) {
							dominantfreq[3] = (float)i+(((float)(data[i-1]-data[i+1]))/((float)(data[i-1]-2*data[i]+data[i+1])))/2;
							dominantfreqp[3] =data[i];
						}
						else{
							if (dominantfreqp[4]<data[i]) {
								dominantfreq[4] = (float)i+(((float)(data[i-1]-data[i+1]))/((float)(data[i-1]-2*data[i]+data[i+1])))/2;
								dominantfreqp[4] =data[i];
							}else{}
						}
					}
				}
			}
		}
		i++;
	}
	/*
	 Serial.println(dominantfreq[0]);
	 Serial.println(dominantfreq[1]);
	 Serial.println(dominantfreq[2]);*/
}