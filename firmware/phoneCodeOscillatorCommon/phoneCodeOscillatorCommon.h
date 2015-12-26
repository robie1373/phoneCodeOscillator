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
    PCOCommon(int ditPin, int dahPin);
    void checkIfConfigure();
  
  private: 
    int _speedPin;
    int _tonePin;
    void _checkIfConfigure(int tonePin, int speedPin);
    void _changeSideTone(boolean direction);
    void _changeCodeSpeed(boolean direction);
};
#endif