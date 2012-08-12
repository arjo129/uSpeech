/**
Part of the uSpeech project
by Arjo
This is a simple classifier that classifies sounds as intoned or unintoned and turns on and off an LED
on pin 12 accordingly. Interestingly since unintoned sounds such as "F" or "s" turn off the light
one can say "on" (purely intoned) to turn on the light and "Off" ( unintoned ) to trurn off the light.
This shows the very crude ability tha uSpeech has to perform speech recognition.   
*/
#include <uspeech.h>
//Initialize the microphone on pin A0
uspeech classifier(A0);
void setup(){
//Calibrate the mic to silence
  classifier.THRESHOLD = 2.0; //This is the constant specific to your amplification system;
  classifier.calibrate();
  Serial.begin(9600);
}
void loop(){
//Perform classification any application using uspeech will have
//to perform the following
  classifier.classify();
//Since uSpeech is designed to allow your arduino to do more
//than just speech recognition the library follows an event
//oriented method
  if(classifier.isReady()){
    //This is pretty obvious
    if(classifier.loudness()>0){
      classifier.getVXCoeff();
      if(classifier.isIntoned()){//All vowels, r, m, n
        Serial.println("a");
        digitalWrite(12,HIGH);
      }
      else{//Letters such as "f","s","z" and are not intoned
      //Because "off" ends with "f" it is not intoned.
        Serial.println("sssssss");
        digitalWrite(12,LOW);
      }
   }
  }
}

