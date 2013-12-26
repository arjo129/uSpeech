#include "uspeech.h"

syllable::syllable(){
    f = 0; e = 0; o = 0; s = 0; h = 0; v = 0;
}
/***
 *  Classify a character into f,e,o,s,h; Call during main loop
 *  @param c    the phoneme
 */
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


#if ARDUINO_ENVIRONMENT > 0
void syllable::debugPrint(){
    Serial.print("[ ");
    Serial.print(f);
    Serial.print(", ");
    Serial.print(e);
    Serial.print(", ");
    Serial.print(o);
    Serial.print(", ");
    Serial.print(v);
    Serial.print(", ");
    Serial.print(h);
    Serial.print(", ");
    Serial.print(s);
    Serial.print("]");
   
}
#endif

int* syllable::tointptr(){
    static int matrix[6];
    matrix[0] = f;
    matrix[1] = e;
    matrix[2] = o;
    matrix[3] = v;
    matrix[4] = h;
    matrix[5] = s;
    return matrix;
}