#include <uspeech.h>

signal voice(A0);
int around = 0;
int maxp =  0;
void setup(){
  voice.calibrate();
  Serial.begin(9600);
}
void loop(){
  voice.sample();
  if(around == 0){
    Serial.println("please remain silent");
  }
  else{
    if(around < 2000){
      if(voice.power()>maxp){
        maxp = voice.power();
      }
    }
    else{
      if(around == 2000){
        Serial.print("SILENCE is");
        Serial.print(maxp);
        Serial.println("Please say ffff");
        maxp = 0;
      }
      else{
        if(around < 8000){
          voice.getPhoneme();
          if(maxp<voice.micPower){
             maxp = voice.micPower;
          }
        }
        else{
        if(around == 8000){
          Serial.print("f1 =");
          Serial.print(maxp);
          Serial.println("now say sss");
        }
        else{
           if(around < 12000){
               voice.getPhoneme();
                if(maxp>voice.micPower){
                   maxp = voice.micPower;
                }
           }
           if(around==12000){
             Serial.print("f2 =");
              Serial.print(maxp);
           }
        }
        }
      }
    }
  }
  around++;
}
