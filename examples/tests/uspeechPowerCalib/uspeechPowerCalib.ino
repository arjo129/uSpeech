#include <uspeech.h>
microphone mic(A0);
void setup(){
  mic.calibrate();
  Serial.begin(9600);
}
void loop(){
  
  Serial.println(mic.power());
}
