#include "uspeech.h"

syllable::syllable(){
    f = 0; e = 0; o = 0; s = 0; h = 0; v = 0;
}
void syllable::classify(char c){
    switch (c) {
        case 'f':
            f++;
            break;
        case 'e':
            e++;
            break;
        case 'o':
            o++;
            break;
        case 'v':
            v++;
            break;
        case 'h':
            h++;
            break;
        case 's':
            s++;
            break;
        default:
            break;
    }
}
int syllable::distance(syllable syl){
    return 0;
}
#ifdef ARDUINO_ENVIRONMENT > 0
void syllable::debugPrint(){
    Serial.print("\nF: ");
    Serial.print(f);
    Serial.print("\nE: ");
    Serial.print(e);
    Serial.print("\nO: ");
    Serial.print(o);
    Serial.print("\nV: ");
    Serial.print(v);
    Serial.print("\nH: ");
    Serial.print(h);
    Serial.print("\nS: ");
    Serial.print(s);
}
#endif