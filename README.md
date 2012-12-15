# uSpeech library #
The uSpeech library provides an interface for voice recognition using the Arduino. It currently produces phonemes, often the library will produce junk phonemes. Please bare with it for the time being. A noise removal function is underway.
##Minimum Requirements ##
The library is quite intensive on the processor. Each sample collection takes about 3.2 milliseconds so pay close attention to the time. The library has been tested on the Arduino Uno (ATMega32). Each signal object uses up 160bytes. No real time scheduler should be used with this.

## Features ##
 - Letter based recognition
 - Small memory footprint
 - Arduino Compatible
 - No training required
 - Fixed point arithmetic
 - 30% - 40% accuracy if based on phonemes, up to 80% if based on words.
 - Plugs directly into an ``analogRead()`` port

## Documentation ##

Commit 40 and above do not have appropriate documentation. To use µSpeech, download a copy of commit 38. 
Head over to the [downloads](https://github.com/arjo129/uSpeech/downloads) section on github and you will find a pdf tutorial.
I'm working on closing the gap in docs please do be patient.
## Algorithm ##
The library utilizes a special algorythm to enable speech detection. First the complexity of the signal is determined by taking
the absolute derivative of the signal multiplying it by a fixed point saclar and then dividing it by the absolute integral of the signal.
Consonants (other than R,L,N and M) have a value above 40 and vowels have a value below 40. To determine the vowel
a filter bank is used and the formants are extracted and matched to [this table](http://en.wikipedia.org/wiki/Formant#Formants_and_phonetics) and determined.
As for consonants, they can be divided into frictaves and plosives. Plosives are like p or b whereas frictaves are like
s or z. Generally each band of the complexity coeficient (abs derivative over abs integral) can be matched to a small set of frictaves
and plosives. The signal determines if it is a plosive or a frictave by watching the length of the utterance (plosives occur over short periods while frictaves over long).
Finally the most appropriate character is chosen.

- [Return to main page](http://arjo129.github.com)
