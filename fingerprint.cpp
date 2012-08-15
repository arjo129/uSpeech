#include "uspeech.h"

fingerprint::fingerprint(uword utterance){
	unsigned long len = utterance.len;
	int mean =(	utterance.vector[0][0]/len+
				utterance.vector[0][1]/len+
				utterance.vector[0][2]/len+
				utterance.vector[0][3]/len)/4;
	
	int mean2 =(utterance.vector[1][0]/len+
				utterance.vector[1][1]/len+
				utterance.vector[1][2]/len+
				utterance.vector[1][3]/len)/5;
	int var = (utterance.vector[0][0]/len-mean+utterance.vector[0][1]/len-mean+utterance.vector[0][2]/len-mean+utterance.vector[0][3]/len-mean)/mean;
	finger[0][0] = (10*(utterance.vector[0][0]/len-mean))/var;
	finger[0][1] = (10*(utterance.vector[0][1]/len-mean))/var;
	finger[0][2] = (10*(utterance.vector[0][2]/len-mean))/var;
	finger[0][3] = (10*(utterance.vector[0][3]/len-mean))/var;
	
	int var2 = (utterance.vector[1][0]/len-mean2+utterance.vector[1][1]/len-mean2+utterance.vector[1][2]/len-mean2+utterance.vector[1][3]/len-mean2)/mean2;
	finger[0][0] = (10*(utterance.vector[1][0]/len-mean))/var;
	finger[0][1] = (10*(utterance.vector[1][1]/len-mean))/var;
	finger[0][2] = (10*(utterance.vector[1][2]/len-mean))/var;
	finger[0][3] = (10*(utterance.vector[1][3]/len-mean))/var;
	finger[0][4] =  utterance.vector[1][4]/len;
}
void fingerprint::debugPrint(){
	Serial.print(finger[0][0]);
	Serial.print("\t");
	Serial.print(finger[1][0]);
	Serial.print("\n");
	Serial.print(finger[0][1]);
	Serial.print("\t");
	Serial.print(finger[1][1]);
	Serial.print("\n");
	Serial.print(finger[0][2]);
	Serial.print("\t");
	Serial.print(finger[1][2]);
	Serial.print("\n");
	Serial.print(finger[0][3]);
	Serial.print("\t");
	Serial.print(finger[1][3]);
	Serial.print("\n");
	Serial.print(finger[0][4]);
	Serial.print("\t");
	Serial.print(finger[1][4]);
	Serial.print("\n");
	Serial.println("----------");
}

pfingerprint::pfingerprint(phoneme utterance){
	int mean =(	utterance.vector[0][0]+
			   utterance.vector[0][1]+
			   utterance.vector[0][2]+
			   utterance.vector[0][3])/4;
	
	int mean2 =(utterance.vector[1][0]+
				utterance.vector[1][1]+
				utterance.vector[1][2]+
				utterance.vector[1][3])/5;
	int var = (utterance.vector[0][0]-mean+utterance.vector[0][1]-mean+utterance.vector[0][2]-mean+utterance.vector[0][3]-mean)/mean;
	finger[0][0] = (10*(utterance.vector[0][0]-mean))/var;
	finger[0][1] = (10*(utterance.vector[0][1]-mean))/var;
	finger[0][2] = (10*(utterance.vector[0][2]-mean))/var;
	finger[0][3] = (10*(utterance.vector[0][3]-mean))/var;
	
	int var2 = (utterance.vector[1][0]-mean2+utterance.vector[1][1]-mean2+utterance.vector[1][2]-mean2+utterance.vector[1][3]-mean2)/mean2;
	finger[0][0] = (10*(utterance.vector[1][0]-mean))/var;
	finger[0][1] = (10*(utterance.vector[1][1]-mean))/var;
	finger[0][2] = (10*(utterance.vector[1][2]-mean))/var;
	finger[0][3] = (10*(utterance.vector[1][3]-mean))/var;
}
void pfingerprint::debugPrint(){
	Serial.print(finger[0][0]);
	Serial.print("\t");
	Serial.print(finger[1][0]);
	Serial.print("\n");
	Serial.print(finger[0][1]);
	Serial.print("\t");
	Serial.print(finger[1][1]);
	Serial.print("\n");
	Serial.print(finger[0][2]);
	Serial.print("\t");
	Serial.print(finger[1][2]);
	Serial.print("\n");
	Serial.print(finger[0][3]);
	Serial.print("\t");
	Serial.print(finger[1][3]);
	Serial.print("\n");
	Serial.print(finger[0][4]);
	Serial.print("\t");
	Serial.print(finger[1][4]);
	Serial.print("\n");
	Serial.println("----------");
}
