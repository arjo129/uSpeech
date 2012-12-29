
#include <uspeech.h>
#define led 13
signal voice(A0);
String collvoice;
char prev;
boolean newline=false;
int sum = 0;
void setup(){
  voice.calibrate();
  Serial.begin(9600);
  pinMode(led, OUTPUT); 
}

void loop(){
    voice.sample();
    char p = voice.getPhoneme();
    if(p!=' '){
      if((p=='f')){
          newline = true;
      }
      else{
          
          newline = false;
      }
    }
    else{
      if(newline){
        digitalWrite(led, LOW);
      }
      else{
        digitalWrite(led, HIGH);
      }
    }
}
