#include "accumulator.h"

Accumulator::Accumulator()
{
    reset();
}

void Accumulator::reset(){
    for(int i = 0 ; i < NUM_PHONES; i++){
        phoneme_count[i] = 0;
    }
    count = 0;
}

void Accumulator::add_phoneme(Phoneme p){
    phoneme_count[p]++;
    count++;
}

bool Accumulator::is_ready(){
   return count  >= samples;
}

void Accumulator::to_probabilities(){
    for(int i = 0 ; i < NUM_PHONES; i++){
        phoneme_count[i] /= SAMPLES;
    }
}
