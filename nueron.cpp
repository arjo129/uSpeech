#include "uspeech.h"
trainedNueron::trainedNueron(char v,char v1, char v2, char v3, char v4, char v10, char v11, char v12, char v13, char v14){
	weights[0][0] = v;
	weights[0][1] = v1;
	weights[0][2] = v2;
	weights[0][3] = v3;
	weights[0][4] = v4;
	weights[1][0] = v10;
	weights[1][1] = v11;
	weights[1][2] = v12;
	weights[1][3] = v13;
	weights[1][4] = v14;
}

unsigned long trainedNueron::input(unsigned long v,unsigned long v1, unsigned long v2, unsigned long v3, unsigned long v4, unsigned long v10, unsigned long v11, unsigned long v12, unsigned long v13, unsigned long v14){
	unsigned longj = v*weights[0][0]+
					v1*weights[0][1]+
					v2*weights[0][2]+
					v3*weights[0][3]+
					v4*weights[0][4]+
					v10*weights[1][0]+
					v11*weights[1][1]+
					v12*weights[1][2]+
					v13*weights[1][3]+
					v14*weights[1][4];
}

