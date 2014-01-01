#include <Servo.h>
#include <uspeech.h>

signal voice(A0);
int time;
bool first =  true, process = false;
syllable s;
Servo myservo;
void left(){
  Serial.println("left(): called");
  myservo.write(0);
}
void right(){
  Serial.println("right(): called");
  myservo.write(180);
}
void center(){
  Serial.println("center(): called");
   myservo.write(90);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);
  voice.f_enabled = true;
  voice.minVolume = 1500;
  voice.fconstant = 400;
  voice.econstant = 1;
  voice.aconstant = 2;
  voice.vconstant = 3;
  voice.shconstant = 4;
  voice.calibrate();
}

void loop() {
  // put your main code here, to run repeatedly: 
  char c = voice.getPhoneme();
  
  if(c==' '){
    if(process){
      int sum = s.f+s.o+s.v+s.s+s.h;
      if(sum>30){
        s.debugPrint();
        Serial.println();
        if(s.f>3){
          if(s.s>3){
            center();
          }
          else{
          left();
          }
        }
        else{
          if(s.s>3){
            center();
          }
          else{
            right();
          }
        }
      }
      s.f = 0;
      s.e = 0;
      s.o = 0;
      s.v = 0;
      s.s = 0;
      s.h = 0;
      process = false;
      
    }
  }
  else{
    if(first){
      time = millis();
    }
    else{
      
    }
    s.classify(c);
    process = true;
  }
}
