#include "uspeech.h"

syllable::syllable(){
    f = 0; e = 0; o = 0; s = 0; h = 0; v = 0; 
	length = 0; cf = 0; ce = 0; co = 0; cs = 0; ch = 0; cv = 0;
	modalityf = 0; modalitye = 0; modalityo = 0; modalitys = 0; modalityh = 0; modalityv = 0;
	expectSp =1; plosiveCount = 0;

}
void syllable::reset(){
    f = 0; e = 0; o = 0; s = 0; h = 0; v = 0;
	length = 0; cf = 0; ce = 0; co = 0; cs = 0; ch = 0; cv = 0;
	modalityf = 0; modalitye = 0; modalityo = 0; modalitys = 0; modalityh = 0; modalityv = 0;
	expectSp =1; plosiveCount = 0;
}
/***
 *  Classify a character into f,e,o,s,h; Call during main loop
 *  @param c    the phoneme
 */
void syllable::classify(char c){
	length++;
	if(expectSp==0){
		if(c!=' '){ //I don't trust the compiler's optimizer
			expectSp = 1;
			if((millis()-lastTime)<MAX_PLOSIVETIME){
				plosiveCount++;
			}
		}
	}
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
		case ' ':
			if(expectSp!=0){
				expectSp = 0;
#if ARDUINO_ENVIRONMENT > 0
				lastTime = millis();
#endif
			}
			else{
			}
			break;
        default:
            break;
    }
	//Repeat every 
	if ((length&PROCESS_SKEWNESS_TIME) == 0){
		if((cf > prevf)&(prevf<PROCESS_SKEWNESS_TIME)){
			prevf = cf;
			maxf = length;
			if(currPeak != 'f'){
				currPeak = 'f';
				modalityf++;
			}
		}
		if((ce > preve)&(preve<PROCESS_SKEWNESS_TIME)){
			preve = ce;
			maxe = length;
			if(currPeak != 'e'){
				currPeak = 'e';
				modalitye++;
			}
		}
		if((co > prevo)&(prevo<PROCESS_SKEWNESS_TIME)){
			prevo = co;
			maxo = length;
			if(currPeak != 'o'){
				currPeak = 'o';
				modalityo++;
			}
		}
		if((cs > prevs)&(prevs<PROCESS_SKEWNESS_TIME)){
			prevs = cs;
			maxs = length;
			if(currPeak != 's'){
				currPeak = 's';
				modalitys++;
			}
		}
		if((ch > prevh)&(prevh<PROCESS_SKEWNESS_TIME)){
			prevh = ch;
			maxh = length;
			if(currPeak != 'h'){
				currPeak = 'h';
				modalityf++;
			}
		}	
		if((cv > prevv)&(prevv<15)){
			prevv = cv;
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
    Serial.print("Accum: [ ");
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
void syllable::distance(syllable s){
}
