/*
PhoneCodeOscillatorCommon.cpp - Library of common functions for use in the board specific firmware versions. Repetition sucks.
Robie Lutsey 26 December, 2015. 
MIT license.
*/

#include "Arduino.h"
#include "phoneCodeOscillatorCommon.h"

PCOCommon::PCOCommon(int ditPin, int dahPin, int speakerPin)
  {
    _speedPin = ditPin;
    _ditPin = ditPin;
    _tonePin = dahPin;
    _dahPin = dahPin;
    _speakerPin = speakerPin;

      // CW characteristics
    sideToneFreq = 622; // should be a pleasant tone in the range CW ops are used to
    wpm = 20;         // operation word per minute
    
    /* Modes: Mode must be _one_ of singleKey, straightKey, or iambic (note capitalization).
    Once you set mode, it sets other variables to mange the tone generation. Don't mess with
    _straightKey or _iambic. Only one of the following _mode statements can be uncommented at
    a time */
    _mode = singleKey;
    //_mode = straightKey;
    //_mode = iambic;

      /* I don't recommend changing anything below here.
      unless you are looking for some Farnsworth action. Then you could
      play with _interLetterLength and _interWordLength to achieve that effect. */
    _ditLength = 1200 / wpm;   // this is the length of a dit in milliseconds at desired WPM
    _dahLength = 3 * _ditLength;
    _interToneLength = _ditLength;
    _interLetterLength = _dahLength;
    _interWordLength = 7 * _ditLength;

    if (_mode == straightKey) { 
      _straightKey = true; 
      _iambic = false; 
    }
    if (_mode == iambic) { 
      _straightKey = false; 
      _iambic = true; 
    }
    if (_mode == straightKey) {
      _straightKey = false;
      _iambic = false;
    }

    // Note that if straightKey is false and iambic is false and both paddles are closed no tone will be sent

    // Play() setup
    // map dit to TRUE and dah to FALSE for use in play
    _dit = true;
    _dah = false;
    sendDit;
    sendDah;
  }

void PCOCommon::_playDit() {
  _now = millis();
  if (_now > _interToneLockTimer) {
    tone(_speakerPin, sideToneFreq, 60);
    _last = _dit;
    _interToneLockTimer = millis() + _interToneLength + _ditLength;
  }
}

void PCOCommon::_playDah() {
  _now = millis();
  if (_now > _interToneLockTimer) {
    tone(_speakerPin, sideToneFreq, 180);
    _last = _dah;
    _interToneLockTimer = millis() + _interToneLength + _dahLength;
  }
}

void PCOCommon::_play(boolean sym) {
  if (sym) {
    _playDit();
  } else {
    _playDah();
  } 
}

void PCOCommon::_diDah() {
  if (digitalRead(_ditPin)==0 && digitalRead(_dahPin)==0) {
    //_play(!_last);
    if (_last) {_playDah();}
    else {_playDit();}
  }
}

void PCOCommon::determineSymbol() {
    if (_straightKey) {
      if (sendDit || sendDah) {
        tone(_speakerPin, sideToneFreq);
      }
      else if (!sendDit && !sendDah) {
        noTone(_speakerPin);
      }
    } else if (sendDit && sendDah) {
      if (_iambic) {
        _diDah();
      }
  } else {
    if (sendDit) {_playDit();}
    else if (sendDah) {_playDah();}
  }
}


void PCOCommon::checkIfConfigure() {
  if (digitalRead(_tonePin) == LOW) {
    _changeSideTone(true);
  }

  if (digitalRead(_speedPin) == LOW) {
    _changeCodeSpeed(true);
  }
}

void PCOCommon::_changeSideTone(boolean direction) {

}

void PCOCommon::_changeCodeSpeed(boolean direction) {

}