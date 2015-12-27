#include <phoneCodeOscillatorCommon.h>


  // Key inputs and
  // sound output. Can be a piezo buzzer, speaker (with amp) or 3mm trs or trrs jack
int ditPin = 2; // Uno 2 has hardware interrupt
int dahPin = 3; // Uno 3 has hardware interrupt
int speakerPin = 5; // Digital pin 5 on uno is basic PWM

PCOCommon pcoCommon(ditPin, dahPin, speakerPin);

void setDit() {pcoCommon.sendDit = true;}
void unsetDit() {pcoCommon.sendDit = false;}
void setDah() {pcoCommon.sendDah = true;}
void unsetDah() {pcoCommon.sendDah = false;}

void setup() 
{ 
  pinMode(ditPin, INPUT_PULLUP);
  pinMode(dahPin, INPUT_PULLUP);
  pcoCommon.checkIfConfigure();

  // set up ditPin to read ditButton on regular Arduinos with 2 hardware interrups
  attachInterrupt(0, setDit, FALLING);
  attachInterrupt(0, unsetDit, RISING);
  
  // set up dahPin to read dahButton on regular Arduinos with 2 hardware interrups
  attachInterrupt(1, setDah, FALLING);
  attachInterrupt(1, unsetDah, RISING);
} 

void loop()
{
  pcoCommon.determineSymbol();
}
