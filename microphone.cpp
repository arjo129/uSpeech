void microphone::sample(){
	char i = 0;
	while(i < 128){
		data[i] = analogRead()-calib;
	}
}
unsigned int microphone::complexity(){
	int power=0, diff=0;
	char i = 1;
	while(i < 128){
		power += abs((int)data[i]);
		diff += abs((int)(data[i]-data[i-1]));
	}
	return (diff*100)/power;
}
void microphone::calibarate(){
}
char microphone::match(){
}
microphone::microphone(int pin){
	port = pin;
}
