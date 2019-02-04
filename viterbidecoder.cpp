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

}

void ViterbiDecoder::set_symbols(uint8_t num){
   num_symbols = num;
}
void ViterbiDecoder::set_word(const uint8_t *word, uint8_t length){
    words = word;
    word_length = length;
    accumulated_probabilities =  (float*)malloc(length*sizeof(float));
    for(int i = 1; i < word_length; i++) accumulated_probabilities[i] = 0.0f;
    accumulated_probabilities[0] = 1.0f;
    new_probabilities = (float*)malloc(length*sizeof(float));
}
void ViterbiDecoder::decode(float* classifier_output){
    for(int i = 0; i < word_length; i++)
        new_probabilities[i] = 0.0f;
    for(int i = 0;  i < word_length-1; i++){
        new_probabilities[i] += classifier_output[words[i]]*accumulated_probabilities[i];
        new_probabilities[i+1] += classifier_output[words[i+1]]*accumulated_probabilities[i];
    }
    new_probabilities[word_length-1] += classifier_output[words[word_length-1]]*accumulated_probabilities[word_length-1];
    for(int i = 0 ; i < word_length; i++)
        accumulated_probabilities[i] = new_probabilities[i];
}
void ViterbiDecoder::reset(){
    samples = 0;
    for(int i = 0; i < num_symbols; i++) accumulated_probabilities[i] = 0;
    accumulated_probabilities[0] = 1;
}
float ViterbiDecoder::get_probability(){
    return accumulated_probabilities[word_length-1];
}

void ViterbiDecoder::debug(){
#ifdef TEST_ENVIRON
    for(int i = 0; i <word_length; i++){
        std::cout << accumulated_probabilities[i] << " ";
    }
    std::cout <<std::endl;
 #endif
}
