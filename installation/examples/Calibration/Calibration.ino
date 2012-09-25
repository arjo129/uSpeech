#include <uspeech.h>
signal voice(A0);
void setup(){
  voice.calibrate();
  Serial.begin(9600);
}
void loop(){
  //Serial.println(voice.getPhoneme());
  voice.sample();
  Serial.println(voice.power());
  
}
