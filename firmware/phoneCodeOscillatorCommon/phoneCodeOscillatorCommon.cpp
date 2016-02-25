/*
PhoneCodeOscillatorCommon.cpp - Library of common functions for use in the 
board specific firmware versions. Repetition sucks.
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
    _configTimeout = 3000;

      // CW characteristics
    sideToneFreq = 622; // should be a pleasant tone in the range CW ops are used to
    wpm = 20;         // operation word per minute
    
    /* Modes: Mode must be _one_ of singlePaddle, straightKey, or iambic (note 
    capitalization). Once you set mode, it sets other variables to mange the 
    tone generation. Don't mess with _straightKey or _iambic. Only one of the 
    following _mode statements can be uncommented at a time */
    //_mode = singlePaddle;
    //_mode = straightKey;
    _mode = iambic;

      /* I don't recommend changing anything below here.
      unless you are looking for some Farnsworth action. Then you could
      play with _interLetterLength and _interWordLength to achieve that 
      effect. */
    _ditLength = 1200 / wpm;   // this is the length of a dit in milliseconds at desired WPM
    _dahLength = 3 * _ditLength;
    _interToneLength = _ditLength;
    _interLetterLength = _dahLength;
    _interWordLength = 7 * _ditLength;

//    bool _straightKey = false;
//    bool _iambic = true; 
//    bool _singlePaddle = false; 

    if (_mode == singlePaddle) { 
      _straightKey = false;
      _iambic = false; 
      _singlePaddle = true; 
    }
    if (_mode == iambic) { 
      _straightKey = false; 
      _iambic = true; 
      _singlePaddle = false; 
    }
    if (_mode == straightKey) {
      _straightKey = true;
      _iambic = false;
      _singlePaddle = false; 
    }

    _inputDelay = 250;
    /* Note that if straightKey is false and iambic is false and both paddles 
    are closed no tone will be sent */

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
    tone(_speakerPin, sideToneFreq, _ditLength);
    _last = _dit;
    _interToneLockTimer = millis() + _interToneLength + _ditLength;
  }
}

void PCOCommon::_playDah() {
  _now = millis();
  if (_now > _interToneLockTimer) {
    tone(_speakerPin, sideToneFreq, _dahLength);
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
//  if (digitalRead(_ditPin)==0 && digitalRead(_dahPin)==0) {
    //_play(!_last);
    if (_last) {_playDah();}
    else {_playDit();}
  //}
}

void PCOCommon::determineSymbol() {
  Serial.print(sendDit);
  Serial.print(", ");
  Serial.println(sendDah);
  Serial.print(_straightKey);
  Serial.print(", ");
  Serial.print(_iambic);
  Serial.print(", ");
  Serial.print(_singlePaddle);
  Serial.print(", ");
  Serial.println(_mode);
    if (_straightKey) {
      if (sendDit || sendDah) {
        Serial.println("_straightKey");
        tone(_speakerPin, sideToneFreq);
      }
      else if (!sendDit && !sendDah) {
        noTone(_speakerPin);
      }
    } 
    
    else if (_iambic) {
      Serial.println("_iambic");
      if (sendDit && sendDah) {
        _diDah();
      }
      else if (sendDit) {
        Serial.print("dit - ");
        Serial.println("iambic");
        _playDit();
      }
      else if (sendDah) {
        _playDah();
        Serial.print("dah - ");
        Serial.println("iambic");
    }
  } 
  
  else if (_singlePaddle) {
    if (sendDit) {
      Serial.print("dit - ");
      Serial.println("fallthrough");
      _playDit();
    }
    else if (sendDah) {
      _playDah();
      Serial.print("dah - ");
      Serial.println("fallthrough");
    }
  }
}

boolean _cM[] = { false, true, false, true, false, false };

void PCOCommon::configMode() {
  int pressCount;
  int _configMode;
  int _pressCount = 0;
  _pressCount ++;
  _configTimer = millis();
  if ( pressCount > 1 ) {
    _pressCount = 1;
    if ( _configMode == 1 ) {
      _configMode == 0;
    }
  }
  if ( _configTimer > _configTimeout ) {
    configRequest = false;
  }
}

void PCOCommon::_changeSideTone() {
  _playDah();
  delay(_inputDelay);
  if ( digitalRead(_ditPin) ) {
    sideToneFreq += 10;
    _playDit();
  }
  else if ( digitalRead(_dahPin) ) {
    sideToneFreq -= 10;
    _playDah();
  }
}

void PCOCommon::_sendCode(boolean menuItem[]) {
    _now = millis();
    if (_now > _interToneLockTimer) {
     for ( int j; j < sizeof(menuItem); j++ ) { 
      Serial.println("beepbeep");
      _play( menuItem[j] );
     }
      _interToneLockTimer = millis() + _interToneLength + _ditLength;
    }
}

