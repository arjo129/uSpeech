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
#include <stdint.h>
#define USPEECH_VSIZE 5
class ViterbiDecoder
{
private:
    uint8_t num_symbols;
#ifndef defined(__AVR_ATmega328P__)
    float* accumulated_probabilities;
    float* new_probabilities;
#endif
#ifdef defined(__AVR_ATmega328P__)
    //For Embedded we want to avoid dynamic memory
    float accumulated_probabilities[USPEECH_VSIZE];
    float new_probabilities[USPEECH_VSIZE];
#endif
    const uint8_t* words;
    uint16_t samples;
    uint8_t word_length;
public:
    ViterbiDecoder();
    void set_symbols(uint8_t num);
    void add_word(const uint8_t* word, uint8_t word_length);
    void decode(float* classifier);
    void reset();
    float get_probability();
};

#endif // VITERBIDECODER_H
