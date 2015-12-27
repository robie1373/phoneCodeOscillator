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
    int sideToneFreq = 622; // should be a pleasant tone in the range CW ops are used to
    int wpm = 20;         // operation word per minute
      // I don't recommend changing anything below here.
      // unless you are looking for some Farnsworth action. Then you could
      // play with interLetterLength and interWordLength to achieve that effect.
    int ditLength = 1200 / wpm;   // this is the length of a dit in milliseconds at desired WPM
    int dahLength = 3 * ditLength;
    int interToneLength = ditLength;
    int interLetterLength = dahLength;
    int interWordLength = 7 * ditLength;
    boolean iambic = false; // Don't use this yet. There is a timing issue to figure out
    // Play() setup
    // map dit to TRUE and dah to FALSE for use in play
    boolean dit = true;
    boolean dah = false;
    boolean sendDit;
    boolean sendDah;
    boolean last;
    unsigned long now;
    unsigned long interToneLockTimer;

  }

void PCOCommon::_checkIfConfigure(int tonePin, int speedPin) {
  if (digitalRead(tonePin) == LOW) {
    _changeSideTone(true);
  }

  if (digitalRead(speedPin) == LOW) {
    _changeCodeSpeed(true);
  }
}

void PCOCommon::playDit() {
  now = millis();
  if (now > interToneLockTimer) {
    tone(_speakerPin, sideToneFreq, ditLength);
  }
  interToneLockTimer = millis() + interToneLength;
  last = dit;
  sendDit = false;
}

void PCOCommon::playDah() {
  now = millis();
  if (now > interToneLockTimer) {
    tone(_speakerPin, sideToneFreq, dahLength);
  }
  interToneLockTimer = millis() + interToneLength;
  last = dah;
  sendDah = false;
}

void PCOCommon::play(boolean sym) {
  if (sym) {
    playDit();
  } else {
    playDah();
  } 
}

void PCOCommon::diDah() {
  if (digitalRead(_ditPin)==0 && digitalRead(_dahPin)==0) {
    //play(!last);
    if (last) { sendDah = true;}
    else {sendDit = true;}
    pause();  // FIXME. How are you going to handle the timing
              // between this pause and the lock in play()?
  }
}

void PCOCommon::pause() {}

void PCOCommon::checkIfConfigure() {
  _checkIfConfigure(_tonePin, _speedPin);
}

void PCOCommon::_changeSideTone(boolean direction) {

}

void PCOCommon::_changeCodeSpeed(boolean direction) {

}