/*
 uspeech v.4.x.x
 2012-2018 Arjo Chakravarty
 MIT License

 uspeech is a library that allows sounds to be classified into certain phonemes
 on the Arduino. This creates a simple beginning for a full scale voice recognition
 program.
*/

#include "viterbidecoder.h"

ViterbiDecoder::ViterbiDecoder()
{
    num_symbols = USPEECH_VSIZE;
}

void ViterbiDecoder::set_symbols(uint8_t num){
#ifndef defined(__AVR_ATmega328P__)
   num_symbols = num;
   accumulated_probabilities = new float[num];
   for(int i = 0; i < num; i++) accumulated_probabilities[i] = 1;
   new_probabilities = new float[num];
#endif
}
void ViterbiDecoder::add_word(const uint8_t *word, uint8_t word_length){
   words = word;
   word_length = word_length;
}
void ViterbiDecoder::decode(float* classifier_output){
    //Initiate all the new_probabilities for t+1
    for(int i = 0; i < num_symbols; i++)
        new_probabilities[i] = 0;
    //Calculate probabilities based on current output and past outputs
    //for transitions and staying in the same state
    for(int i = 0; i < word_length-1; i++){
        new_probabilities[words[i+1]] += classifier_output[words[i+1]] * accumulated_probabilities[words[i]];
        new_probabilities[words[i]] += classifier_output[words[i]] * accumulated_probabilities[words[i]];
    }
    //copy new probabilities into table
    for(int i = 0; i < num_symbols; i++)
        accumulated_probabilities[i] = new_probabilities[i];
    //increment samples
    samples++;
}
void ViterbiDecoder::reset(){
    samples = 0;
    for(int i = 0; i < num_symbols; i++) accumulated_probabilities[i] = 1;
}
float ViterbiDecoder::get_probability(){
    return accumulated_probabilities[words[word_length-1]];
}
