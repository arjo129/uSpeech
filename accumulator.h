#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H
#define NUM_PHONES 6
#define samples 40
typedef enum {
    O = 0,
    E = 1,
    F = 2,
    V = 3,
    H = 4,
    S = 5
} Phoneme;

class Accumulator
{
public:
    float phoneme_count[NUM_PHONES];
    int count;
    Accumulator();
    void reset();
    void add_phoneme(Phoneme c);
    bool is_ready();
};

#endif // ACCUMULATOR_H
