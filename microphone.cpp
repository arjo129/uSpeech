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
//Taken from the 8bit FFT on the arduino Forums. See FFT.cpp fo
//Full credit
/*
 fix_fft() - perform forward/inverse fast Fourier transform.
 fr[n],fi[n] are real and imaginary arrays, both INPUT AND
 RESULT (in-place FFT), with 0 <= n < 2**m; set inverse to
 0 for forward transform (FFT), or 1 for iFFT.
 */
int fix_fft(char fr[], char fi[], int m, int inverse);



/*
 fix_fftr() - forward/inverse FFT on array of real numbers.
 Real FFT/iFFT using half-size complex FFT by distributing
 even/odd samples into real/imaginary arrays respectively.
 In order to save data space (i.e. to avoid two arrays, one
 for real, one for imaginary samples), we proceed in the
 following two steps: a) samples are rearranged in the real
 array so that all even samples are in places 0-(N/2-1) and
 all imaginary samples in places (N/2)-(N-1), and b) fix_fft
 is called with fr and fi pointing to index 0 and index N/2
 respectively in the original array. The above guarantees
 that fix_fft "sees" consecutive real samples as alternating
 real and imaginary samples in the complex array.
 */
int fix_fftr(char f[], int m, int inverse);
