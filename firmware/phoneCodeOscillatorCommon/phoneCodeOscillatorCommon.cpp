/*
PhoneCodeOscillatorCommon.cpp - Library of common functions for use in the board specific firmware versions. Repetition sucks.
Robie Lutsey 26 December, 2015. 
MIT license.
*/

#include "Arduino.h"
#include "phoneCodeOscillatorCommon.h"

PCOCommon::PCOCommon(int ditPin, int dahPin)
  {
    _speedPin = ditPin;
    _tonePin = dahPin;
  }

void PCOCommon::_checkIfConfigure(int tonePin, int speedPin) {
  if (digitalRead(tonePin) == LOW) {
    _changeSideTone(true);
  }

  if (digitalRead(speedPin) == LOW) {
    _changeCodeSpeed(true);
  }
}

void PCOCommon::checkIfConfigure() {
  _checkIfConfigure(_tonePin, _speedPin);
}

void PCOCommon::_changeSideTone(boolean direction) {

}

void PCOCommon::_changeCodeSpeed(boolean direction) {

}