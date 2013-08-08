#include <uspeech.h>
signal voice(A0);
char option = 0;
void setup(){
  voice.calibrate();
  Serial.begin(9600);
}
void loop(){
  voice.sample();
  char c=voice.getPhoneme();
  if(option==0){
    Serial.println("uSpeech debug tool--------");
    Serial.println(" Press 'a' if you wish to calibrate/check the f algorithm");
    Serial.println(" Press 'b' if you wish to calibrate/check the getPhoneme");
    Serial.println(" Press 'c' if you wish to calibrate/check the volume of your microphone");
    Serial.println(" Press 'd' if you wish to calibrate/check the coeff");
    Serial.println(" Press 'e' if you wish to calibrate/check the vowel detector");   
    option = 1;
  }
  if(option==1){
   if (Serial.available() > 0) {
                // read the incoming byte:
                option = Serial.read();
   }
  }
  if(option=='a'){
    Serial.println(voice.micPower);
  }
  if(option=='b'){
    Serial.println(c);
  }
  if(option=='c'){
    Serial.println(voice.power());
  }
  if(option=='d'){
  	Serial.println(voice.testCoeff);
  }
  if(option=='e'){
    
    Serial.println(voice.vowelRatio);
  }
}