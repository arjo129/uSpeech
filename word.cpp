#include "uspeech.h"

uword::uword(){
	vector[0][0] = 0; vector[1][0] = 0;
	vector[0][1] = 0; vector[1][1] = 0;
	vector[0][2] = 0; vector[1][2] = 0;
	vector[0][3] = 0; vector[1][3] = 0;
	vector[0][4] = 0; vector[1][4] = 0;
}
void uword::reset(){
	vector[0][0] = 0; vector[1][0] = 0;
	vector[0][1] = 0; vector[1][1] = 0;
	vector[0][2] = 0; vector[1][2] = 0;
	vector[0][3] = 0; vector[1][3] = 0;
	vector[0][4] = 0; vector[1][4] = 0;
}
void uword::debugPrint(){
	Serial.print(vector[0][0]);
  Serial.print("\t");
  Serial.print(vector[1][0]);
  Serial.print("\n");
  Serial.print(vector[0][1]);
  Serial.print("\t");
  Serial.print(vector[1][1]);
  Serial.print("\n");
  Serial.print(vector[0][2]);
  Serial.print("\t");
  Serial.print(vector[1][2]);
  Serial.print("\n");
  Serial.print(vector[0][3]);
  Serial.print("\t");
  Serial.print(vector[1][3]);
  Serial.print("\n");
  Serial.print(vector[0][4]);
  Serial.print("\t");
  Serial.print(vector[1][4]);
  Serial.print("\n");
  Serial.println("----------");
}
int uword::confidence(){
	return vector[0][4];
}
void uword::attachPhoneme(phoneme P){
	len++;
	vector[0][0] += P.vector[0][0]; vector[1][0] += P.vector[1][0];
	vector[0][1] += P.vector[0][1]; vector[1][1] += P.vector[1][1];
	vector[0][2] += P.vector[0][2]; vector[1][2] += P.vector[1][2];
	vector[0][3] += P.vector[0][3]; vector[1][3] += P.vector[1][3];
	vector[0][4] += P.vector[0][4]; vector[1][4] += P.vector[1][4];
}