#include "uspeech.h"
/*<c> Arjo Chakravarty MIT License
 *This file contains the peak detection and sorting functions
 */


/** Extract coefficients
 *  Finds the dominant frequencies of a microphone 
 *	1 - Takes the FFT and finds peaks	[done]
 *  2 - Finds the top 5 peaks			[done]
 *	3 - Records their frequencies		[done]
 *	Status: Ready for testing
 *  Input: none
 *	Return: none
 */
void microphone::extractCoefficients(){
	char peaks[127]; // Storage of all peaks
	int i =1;

	while(i<128){
		if(data[i-1]<data[i]&&data[i]>data[i-1]){
			peaks[i] = data[i];
		}
		i++;
	}
	i = 0;
	char maxv=0,maxn;
	while(i<127){
		if(peaks[i]>maxv){
			maxv = peaks[i];
			maxn = i;
		}
		i++;
	}
	dominantfreq[0]=maxn;
	peaks[maxn] = 0;
	maxv=0,maxn=0;
	i =0;
	while(i<127){
		if(peaks[i]>maxv){
			maxv = peaks[i];
			maxn = i;
		}
		i++;
	}i = 0;
	dominantfreq[1]=maxn;
	peaks[maxn] = 0;
	maxv=0,maxn=0;
	while(i<127){
		if(peaks[i]>maxv){
			maxv = peaks[i];
			maxn = i;
		}
		i++;
	}i = 0;
	dominantfreq[2]=maxn;
	peaks[maxn] = 0;
	maxv=0,maxn=0;
	while(i<127){
		if(peaks[i]>maxv){
			maxv = peaks[i];
			maxn = i;
		}
		i++;
	}i = 0;
	dominantfreq[3]=maxn;
	peaks[maxn] = 0;
	maxv=0,maxn=0;
	while(i<127){
		if(peaks[i]>maxv){
			maxv = peaks[i];
			maxn = i;
		}
		i++;
	}i = 0;
	dominantfreq[4]=maxn;
	peaks[maxn] = 0;
	
}