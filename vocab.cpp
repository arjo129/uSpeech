#include "uspeech.h"

syllable::syllable(){
    f = 0; e = 0; o = 0; s = 0; h = 0; v = 0; 
	length = 0; cf = 0; ce = 0; co = 0; cs = 0; ch = 0; cv = 0;
	modalityf = 0; modalitye = 0; modalityo = 0; modalitys = 0; modalityh = 0; modalityv = 0;
}
void syllable::reset(){
    f = 0; e = 0; o = 0; s = 0; h = 0; v = 0;
	length = 0; cf = 0; ce = 0; co = 0; cs = 0; ch = 0; cv = 0;
	modalityf = 0; modalitye = 0; modalityo = 0; modalitys = 0; modalityh = 0; modalityv = 0;
}
/***
 *  Classify a character into f,e,o,s,h; Call during main loop
 *  @param c    the phoneme
 */
void syllable::classify(char c){
	length++;
    switch (c) {
        case 'f':
            f++;
			cf++;
            break;
        case 'e':
            e++;
			ce++;
            break;
        case 'o':
            o++;
			co++;
            break;
        case 'v':
            v++;
			cv++;
            break;
        case 'h':
            h++;
			ch++;
            break;
        case 's':
            s++;
			cs++;
            break;
        default:
            break;
    }
	//Repeat 16 times
	if ((length&15) == 0){
		if((cf > prevf)&(prevf<15)){
			prevf = cf;
			maxf = length;
			if(currPeak != 'f'){
				currPeak = 'f';
				modalityf++;
			}
		}
		if((ce > preve)&(preve<15)){
			preve = ce;
			maxe = length;
			if(currPeak != 'e'){
				currPeak = 'e';
				modalitye++;
			}
		}
		if((co > prevo)&(prevo<15)){
			prevo = co;
			maxo = length;
			if(currPeak != 'o'){
				currPeak = 'o';
				modalityo++;
			}
		}
		if((cs > prevs)&(prevs<15)){
			prevs = cs;
			maxs = length;
			if(currPeak != 's'){
				currPeak = 's';
				modalitys++;
			}
		}
		if((ch > prevh)&(prevh<15)){
			prevh = ch;
			maxh = length;
			if(currPeak != 'h'){
				currPeak = 'h';
				modalityf++;
			}
		}	
		if((cv > prevv)&(prevv<15)){
			prevcv = cv;
			maxv = length;
			if(currPeak != 'v'){
				currPeak = 'v';
				modalityf++;
			}
		}
		cf = 0; ce = 0; co = 0; cs = 0; ch = 0; cv = 0;
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
void syllable::distance(){
}
