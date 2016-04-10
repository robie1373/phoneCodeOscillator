/*
PhoneCodeOscillatorCommon.cpp - Library of common functions for use in the 
board specific firmware versions. Repetition sucks.
Robie Lutsey 26 December, 2015. 
MIT license.
*/

#include "Arduino.h"
#include "morseGen.h"
#include "morseTable.ino"

String _text;

// Call IngestText with an ascii text string. Source can be whatever you want.
void MorseGen::initialize(String _input) { 
  _text = String.toUpperCase(_input);
}

char MorseGen::_getNextCharacter() { 
  char _nextChar = _text[0];
  _text.remove(0, 1);
  return _nextChar;
}

void MorseGen::_sendCharacter(char _c, PCOCommon _PCOCommon) { 
  byte _i = morseTable[_c];
  if ( _i != 1 ) {
    byte _thisBit = bitRead(_i, 0);
    _i >> 1;
    if (_thisBit == 0) {
      _PCOCommon.sendDit();
    else _PCOCommon.sendDah();
    }
  }
}

void MorseGen::SendCode(PCOCommon _PCOCommon) { 
  if (String.length(_text) > 0) {
    char _thisCharacter = _getNextCharacter();
    _sendCharacter(_thisCharacter, _PCOCommon);
  }
}
