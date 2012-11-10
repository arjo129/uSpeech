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
	while(i<128){
		if(data[i-1]<data[i]&&data[i]>data[i-1]){
			if(dominantfreqp[0]<data[i]){
				dominantfreq[0]=i;
				dominantfreqp[0] =data[i];
			}
			else{ 
				if (dominantfreqp[1]<data[i]) {
					dominantfreq[1] =i;
					dominantfreqp[1] =data[i];
				}
				else{
					if (dominantfreqp[2]<data[i]) {
						dominantfreq[2] =i;
						dominantfreqp[2] =data[i];
					}
					else{
						if (dominantfreqp[3]<data[i]) {
							dominantfreq[3] =i;
							dominantfreqp[3] =data[i];
						}
						else{
							if (dominantfreqp[4]<data[i]) {
								dominantfreq[4] =i;
								dominantfreqp[4] =data[i];
							}else{}
						}
					}
				}
			}
		}
		i++;
	}
	
}