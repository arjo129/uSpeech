#include "uspeech.h"
uspeech::uspeech(int pin) {
	sensorPin = pin;    
	//calib = analogRead(pin);      
	sensorValue = 0;  // variable to store the value coming from the sensor
	prev = 0;
	iter = 0; // Iterator
	sum = 0;
	dif = 0;
	state = true;
	nt = 1;
	mvAvg = 0;
	haveread = false;

}
void uspeech::calibrate(){
	calib = ((float)analogRead(sensorPin)+(float)analogRead(sensorPin)+(float)analogRead(sensorPin)+(float)analogRead(sensorPin)+(float)analogRead(sensorPin)+(float)analogRead(sensorPin))/6.0;
}
void uspeech::classify(){
	sensorValue = (float)analogRead(sensorPin);  
	sensorValue = calib-sensorValue;
	//Serial.println(sensorValue);
	sum += abs(sensorValue);
	dif += abs(sensorValue-prev);
	prev = sensorValue;
	iter++;
	if(iter == SAMPLEWINDOW){
		haveread = true;
		iter = 0;
		
		if(sum!=0){
			if(nt == 6){
				nt = 1;
				mvAvg = 0;
			}
			float stat = (dif/sum + mvAvg)/nt;
			mvAvg =stat*nt;
			nt++;
			
			prev = sum;
			prev2 = dif;
			sum = 0;
			dif  = 0;
			
			if(stat>THRESHOLD){
				state = false;
				//Serial.println("unintoned");
       
     
			}
			else{
				state = true;
				//Serial.println(stat);
			}
		}
	}
}
float uspeech::loudness(){
	haveread = false;
	return prev;
}
float uspeech::getVXCoeff(){
	haveread = false;

	return prev2/prev;
}
bool uspeech::isReady(){
	//
	return haveread;
}
bool uspeech::isIntoned(){
	//Serial.println(prev2/prev);
	haveread = false;
	return state;
}

