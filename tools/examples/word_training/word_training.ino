/**Basic training
*P gives a matrix for recognizing the phoneme
*I advice you use the uspeech library along with gaussian
*modelling toolkit this will allow yout to use the library
*for picking up sound
*/
#include <uspeech.h>
int t;
uspeech recognizer(A0);
uword words;
bool printed= true;
void setup(){
  Serial.begin(9600);
  recognizer.calibrate();
}
void loop(){
  phoneme p= recognizer.get();
  if(p.loudness()>3){
    words.attachPhoneme(p);
    printed = false;
  }
  else{
    if(t == 0){
      t =millis();
    }
    if(millis()-t>500){
      t = 0;
      if(!printed){
        if(words.confidence()>60){
          words.debugPrint();
          words.reset();
          printed = true;
        }
        printed = true;
      }
    }
  }
}
