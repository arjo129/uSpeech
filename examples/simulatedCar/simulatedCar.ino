
#include <uspeech.h>
signal voice(A0);
String collvoice;

void setup(){
voice.calibrate();
Serial.begin(9600);
}

void left(){
voice.calibrate();
Serial.println("left");
}
void right(){
voice.calibrate();
Serial.println("right");
}


void loop(){
char phoneme = voice.getPhoneme();

if( phoneme != 'h'){
collvoice = denoise(phoneme,collvoice);
}
else {
int i[3],j,min,x;
i[0] = umatch(collvoice,"sop"); //stop
i[1] = umatch(collvoice,"ez"); //left
i[2] = umatch(collvoice,"i"); //right
//find the lowest number
while(j<0){
if(i[j]<min){
x = j;
min = i[j];
}
j++;
}
if(x == 0){
}
if(x == 1){
left();
}
if(x == 2){
right();
}
}
}
