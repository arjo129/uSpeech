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
	char out = 0, ret = 0;
	int max = 0;
	while(out<10){
		if(max<o[out]){
			ret = out;
			max = o[out];
		}
	}
	return ret;
}
void knueralnet::train(){
	list<uword> i1,i2,i3,i4,i5,i6,i7,i8,i9,i10;
	//Attach your uwords to these lists
	randWeight();
	int i = 0;
	for (i1::const_iterator ci = intList.begin(); ci != intList.end(); ci++){
         char j = classify(*ci);
		 if(j!=0){
			 
		 }
	}
}
void knueralnet::randWeight(){
	int i = 0, j = 0;
	srand ( time(NULL) );
	while(i<10){
		while(j<10){
			weights[i][j] = rand()%110+1;
			j++;
		}
		i++;
	}
}
void knueralnet::adjustWeights(char in, char des){
}