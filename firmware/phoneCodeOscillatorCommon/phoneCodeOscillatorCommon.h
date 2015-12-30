/*
PhoneCodeOscillatorCommon.h - Library of common functions for use in the board specific firmware versions. Repetition sucks.
Robie Lutsey 26 December, 2015. 
MIT license.
*/

#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class PCOCommon 
{
  public: 
    PCOCommon(int ditPin, int dahPin, int speakerPin);
    void checkIfConfigure();
    int sideToneFreq;
    int wpm;
    int ditLength;
    int dahLength;
    int interToneLength;
    int interLetterLength;
    int interWordLength;
    boolean iambic;
    boolean dit;
    boolean dah;
    boolean sendDit;
    boolean sendDah;
    boolean last;
    unsigned long now;
    unsigned long interToneLockTimer;
    void playDit();
    void playDah();
    void play(boolean sym);
    void pause();
    void diDah();
    void determineSymbol();

  
  private: 
    int _ditPin;
    int _dahPin;
    int _speedPin;
    int _tonePin;
    int _speakerPin;

    void _checkIfConfigure(int tonePin, int speedPin);
    void _changeSideTone(boolean direction);
    void _changeCodeSpeed(boolean direction);
};
#endif