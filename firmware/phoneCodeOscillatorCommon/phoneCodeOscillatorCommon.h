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
    int sideToneFreq;
    int wpm;

    boolean sendDit;
    boolean sendDah;
    void checkIfConfigure();
    void determineSymbol();

  
  private: 
    int _ditPin;
    int _dahPin;
    int _speedPin;
    int _tonePin;
    int _speakerPin;
    boolean _straightKey;
    boolean _iambic;
    int _mode;
    const int singleKey = 1;
    const int straightKey = 2;
    const int iambic = 3;
    int _ditLength;
    int _dahLength;
    int _interToneLength;
    int _interLetterLength;
    int _interWordLength;
    unsigned long _now;
    unsigned long _interToneLockTimer;
    boolean _last;
    boolean _dit;
    boolean _dah;
    void _playDit();
    void _playDah();
    void _play(boolean sym);
    void _diDah();

    void _changeSideTone(boolean direction);
    void _changeCodeSpeed(boolean direction);
};
#endif