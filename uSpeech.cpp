#include "uspeech.h"
uspeech::uspeech(int ipin){
	pin = ipin;
}
void uspeech::calibrate(){
	calib = (analogRead(pin)+analogRead(pin)+analogRead(pin)+analogRead(pin))/4;
}
phoneme uspeech::get(){
	resetAll();
	sample();
	filterx1();
	filterx2();
	filterx3();  
	filterx4();
	complexity();
	phoneme p(vector[0][0],vector[0][1],vector[0][2],vector[0][3],vector[0][4],vector[1][0],vector[1][1],vector[1][2],vector[1][3],vector[1][4]);
	return p;
}
void uspeech::resetAll(){
	int i = 0;
  while(i<32){
    arr[i] = 0;
    filter4[i] = 0;
    i++;
  }
  vector[0][0] = 0;
  vector[0][1] = 0;
  vector[0][2] = 0;
  vector[0][3] = 0;
  vector[0][4] = 0;
  vector[1][0] = 0;
  vector[1][1] = 0;
  vector[1][2] = 0;
  vector[1][3] = 0;
  vector[1][4] = 0;
}
void uspeech::sample(){
	arr[0] = analogRead(pin)-calib;
  arr[1] = analogRead(pin)-calib;
  arr[2] = analogRead(pin)-calib;
  arr[3] = analogRead(pin)-calib;
  arr[4] = analogRead(pin)-calib;
  arr[5] = analogRead(pin)-calib;
  arr[6] = analogRead(pin)-calib;
  arr[7] = analogRead(pin)-calib;
  arr[8] = analogRead(pin)-calib;
  arr[9] = analogRead(pin)-calib;
  arr[10] = analogRead(pin)-calib;
  arr[11] = analogRead(pin)-calib;
  arr[12] = analogRead(pin)-calib;
  arr[13] = analogRead(pin)-calib;
  arr[14] = analogRead(pin)-calib;
  arr[15] = analogRead(pin)-calib;
  arr[16] = analogRead(pin)-calib;
  arr[17] = analogRead(pin)-calib;
  arr[18] = analogRead(pin)-calib;
  arr[19] = analogRead(pin)-calib;
  arr[20] = analogRead(pin)-calib;
  arr[21] = analogRead(pin)-calib;
  arr[22] = analogRead(pin)-calib;
  arr[23] = analogRead(pin)-calib;
  arr[24] = analogRead(pin)-calib;
  arr[25] = analogRead(pin)-calib;
  arr[26] = analogRead(pin)-calib;
  arr[27] = analogRead(pin)-calib;
  arr[28] = analogRead(pin)-calib;
  arr[29] = analogRead(pin)-calib;
  arr[30] = analogRead(pin)-calib;
  arr[31] = analogRead(pin)-calib;
  arr[32] = analogRead(pin)-calib;
}
void uspeech::filterx1(){
	filter1[0] = fmean(25,0);
  filter1[1] = fmean(25,1);
  filter1[2] = fmean(25,2);
  filter1[3] = fmean(25,3);
  filter1[4] = fmean(25,4);
  filter1[5] = fmean(25,5);
  filter1[6] = fmean(25,6);
  filter1[7] = fmean(25,7);
  vector[0][0] = abs(filter1[0])+abs(filter1[1])+abs(filter1[2])+abs(filter1[3])+abs(filter1[4])+abs(filter1[5])+abs(filter1[6])+abs(filter1[7]);
  vector[1][0] = 100*(abs(filter1[1]-filter1[0])+abs(filter1[2]-filter1[1])+abs(filter1[3]-filter1[2])+abs(filter1[4]-filter1[3])+abs(filter1[5]-filter1[4])+abs(filter1[6]-filter1[5])+abs(filter1[7]-filter1[6]))/vector[0][0];
  vector[0][0] = vector[0][0]/8;
}
void uspeech::filterx2(){
	filter2[0] = fmean(17,0)- filter1[0];
  filter2[1] = fmean(17,1)- filter1[0];
  filter2[2] = fmean(17,2)- filter1[1];
  filter2[3] = fmean(17,3)- filter1[1];
  filter2[4] = fmean(17,4)- filter1[2];
  filter2[5] = fmean(17,5)- filter1[2];
  filter2[6] = fmean(17,6)- filter1[3];
  filter2[7] = fmean(17,7)- filter1[3];
  filter2[8] = fmean(17,8)-  filter1[4];
  filter2[9] = fmean(17,9)-  filter1[4];
  filter2[10] = fmean(17,10)-  filter1[5];
  filter2[11] = fmean(17,11)-  filter1[5];
  filter2[12] = fmean(17,12)-  filter1[6];
  filter2[13] = fmean(17,13)-  filter1[6];
  filter2[14] = fmean(17,14)-  filter1[7];
  vector[0][1] = sumf2()/15;
  vector[1][1] = (dif2()*100)/sumf2();
}
int uspeech::sumf2(){
	  int i =0;
  int j = 0;
  while(i<15){
    j += abs(filter2[i]);
    i++;
  }
  return j;
}
int uspeech::dif2(){
	  int i =0;
  int j = 0;
  while(i<15){
    j += abs(filter2[i]-filter2[i-1]);
    i++;
  }
  return j;
}
void uspeech::filterx3(){
	filter3[0] = fmean(12,0)- filter2[0] -filter1[0];
  filter3[1] = fmean(12,1)- filter2[0] -filter1[0];
  filter3[2] = fmean(12,2)- filter2[1] -filter1[1];
  filter3[3] = fmean(12,4)- filter2[2] -filter1[1];
  filter3[4] = fmean(12,3)- filter2[2] -filter1[2];
  filter3[5] = fmean(12,5)- filter2[3] -filter1[2];
  filter3[6] = fmean(12,6)- filter2[4] -filter1[3];
  filter3[7] = fmean(12,7)- filter2[4] -filter1[3];
  filter3[8] = fmean(12,8)- filter2[5] -filter1[3];
  filter3[9] = fmean(12,9)- filter2[6] -filter1[4];
  filter3[10] = fmean(12,10)- filter2[6] -filter1[4];
  filter3[11] = fmean(12,11)- filter2[7] -filter1[4];
  filter3[12] = fmean(12,12)- filter2[8] -filter1[5];
  filter3[13] = fmean(12,13)- filter2[8] -filter1[5];
  filter3[14] = fmean(12,14)- filter2[9] -filter1[6];
  filter3[15] = fmean(12,15)- filter2[10] -filter1[6];
  filter3[16] = fmean(12,16)- filter2[11] -filter1[6];
  filter3[17] = fmean(12,17)- filter2[12] -filter1[7];
  filter3[18] = fmean(12,18)- filter2[13] -filter1[7];
  filter3[19] = fmean(12,19)- filter2[14] -filter1[7];
  vector[0][2] = sumf3()/20;
  vector[1][2] = (dif3()*100)/sumf3();
}
int uspeech::sumf3(){
  int i =0;
  int j = 0;
  while(i<20){
    j += abs(filter3[i]);
    i++;
  }
  return j;
}
int uspeech::dif3(){
  int i =0;
  int j = 0;
  while(i<20){
    j += abs(filter3[i]-filter3[i-1]);
    i++;
  }
  return j;
}
void uspeech::filterx4(){
  filter4[0] = arr[0]-filter3[0] -filter2[0] -filter1[0];
  filter4[1] = arr[1]-filter3[1] -filter2[0] -filter1[0];
  filter4[2] = arr[2]-filter3[1] -filter2[1] -filter1[0];
  filter4[3] = arr[3]-filter3[2] -filter2[1] -filter1[0];
  filter4[4] = arr[4]-filter3[3] -filter2[2] -filter1[1];
  filter4[5] = arr[5]-filter3[3] -filter2[2] -filter1[1];
  filter4[6] = arr[6]-filter3[4] -filter2[3] -filter1[1];
  filter4[7] = arr[7]-filter3[5] -filter2[3] -filter1[1];
  filter4[8] = arr[8]-filter3[5] -filter2[4] -filter1[2];
  filter4[9] = arr[9]-filter3[6] -filter2[4] -filter1[2];
  filter4[10] = arr[10]-filter3[7] -filter2[5] -filter1[2];
  filter4[11] = arr[11]-filter3[7] -filter2[5] -filter1[2];
  filter4[12] = arr[12]-filter3[8] -filter2[6] -filter1[3];
  filter4[13] = arr[13]-filter3[9] -filter2[6] -filter1[3];
  filter4[14] = arr[14]-filter3[9] -filter2[7] -filter1[3];
  filter4[15] = arr[15]-filter3[10] -filter2[7] -filter1[3];
  filter4[16] = arr[16]-filter3[11] -filter2[8] -filter1[4];
  filter4[17] = arr[17]-filter3[11] -filter2[8] -filter1[4];
  filter4[18] = arr[18]-filter3[12] -filter2[9] -filter1[4];
  filter4[19] = arr[19]-filter3[13] -filter2[9] -filter1[4];
  filter4[20] = arr[20]-filter3[13] -filter2[10] -filter1[5];
  filter4[21] = arr[21]-filter3[14] -filter2[10] -filter1[5];
  filter4[22] = arr[22]-filter3[15] -filter2[11] -filter1[5];
  filter4[23] = arr[23]-filter3[15] -filter2[11] -filter1[5];
  filter4[24] = arr[24]-filter3[16] -filter2[12] -filter1[6];
  filter4[25] = arr[25]-filter3[17] -filter2[12] -filter1[6];
  filter4[26] = arr[26]-filter3[17] -filter2[13] -filter1[6];
  filter4[27] = arr[27]-filter3[18] -filter2[13] -filter1[6];
  filter4[28] = arr[28]-filter3[18] -filter2[13] -filter1[7];
  filter4[29] = arr[29]-filter3[19] -filter2[14] -filter1[7];
  filter4[30] = arr[30]-filter3[19] -filter2[14] -filter1[7];
  filter4[31] = arr[31]-filter3[19] -filter2[14] -filter1[7];
  vector[0][3] = sumf4()/32;
  vector[1][3] = (dif4()*100)/sumf4();}
int uspeech::sumf4(){
  int i =0;
  int j = 0;
  while(i<32){
    j += abs(filter4[i]);
    i++;
  }
  return j;
}
int uspeech::dif4(){
  int i =0;
  long j = 0;
  while(i<32){
    j += abs(filter4[i]-filter4[i-1]);
    i++;
  }
  return j;
}
int uspeech::fmean(int freq, int start){
  int i = start;
  long j = 0;
  while(i<freq){
    j += arr[i];
    i++;
  }  
  return j/freq;
}
void uspeech::complexity(){
  vector[0][4] =   sumOverall()/32;
  vector[1][4] = (difOverall()*100)/sumOverall();
}
int uspeech::sumOverall(){
  int i =0;
  int j = 0;
  while(i<32){
    j += abs(arr[i]);
    i++;
  }
  return j;
}
int uspeech::difOverall(){
  int i =0;
  int j = 0;
  while(i<20){
    j += abs(arr[i]-arr[i-1]);
    i++;
  }
  return j;
}
phoneme::phoneme(int v,int v1, int v2, int v3, int v4, int v10, int v11, int v12, int v13, int v14){
	vector[0][0] = v;
	vector[0][1] = v1;
	vector[0][2] = v2;
	vector[0][3] = v3;
	vector[0][4] = v4;
	vector[1][0] = v10;
	vector[1][1] = v11;
	vector[1][2] = v12;
	vector[1][3] = v13;
	vector[1][4] = v14;
}
void phoneme::debugPrint(){
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
int phoneme::loudness(){
	return vector[0][4];
}
int modelPhoneme::getDistance(phoneme p){
	int j = 0;
	int i = 0;
	while(i<5){
		j+=abs(p.vector[0][i]-mean[0][i])/stdev[0][i];
		j+=abs(p.vector[1][i]-mean[1][i])/stdev[1][i];
		i++;
	}
	return j;
}
 modelPhoneme:: modelPhoneme(){
 }