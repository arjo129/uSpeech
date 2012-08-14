#include "uspeech.h"
knueralnet::knueralnet(char output){
	outputs = output;
}
char knueralnet::classify(phoneme p){
	int i=0;
	//Values of nueral network outputs
	int j = 0;
	while(j<10){
		while(i<5){
			o[j]+=p.vector[0][i]*weights[i][j];
			o[j]+=p.vector[1][i]*weights[i+5][j];
			i++;
		}
		j++;
	}
	char out = 0, ret;
	int max = 0;
	while(out<10){
		if(max<o[out]){
			ret = out;
			max = o[out];
		}
	}
	return ret;
}

char knueralnet::classify(uword text){
	int i=0;
	//Values of nueral network outputs
	int j =0;
	while(j<10){
		while(i<5){
			o[j]+=text.vector[0][i]/text.len*weights[i][j];
			o[j]+=text.vector[1][i]/text.len*weights[i+5][j];
			i++;
		}
		j++;
	}
	char out = 0, ret;
	int max = 0;
	while(out<10){
		if(max<o[out]){
			ret = out;
			max = o[out];
		}
	}
	return ret;
}
