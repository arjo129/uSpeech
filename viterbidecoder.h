/*
 uspeech v.4.x.x
 2012-2018 Arjo Chakravarty
 MIT License

 uspeech is a library that allows sounds to be classified into certain phonemes
 on the Arduino. This creates a simple beginning for a full scale voice recognition
 program.
*/
#ifndef VITERBIDECODER_H
#define VITERBIDECODER_H
#ifdef TEST_ENVIRON
#include <stdint.h>
#include <iostream>
#include <stdlib.h>
#endif

class ViterbiDecoder
{
private:
    uint8_t num_symbols;
    float* accumulated_probabilities;
    float* new_probabilities;
    const uint8_t* words;
    uint16_t samples;
    uint8_t word_length;
public:
    ViterbiDecoder();
    void set_symbols(uint8_t num);
    void set_word(const uint8_t* word, uint8_t length);
    void decode(float* classifier);
    void reset();
    float get_probability();
    void debug();
};

#endif // VITERBIDECODER_H
