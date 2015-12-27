#include <phoneCodeOscillatorCommon.h>


  // Key inputs and
  // sound output. Can be a piezo buzzer, speaker (with amp) or 3mm trs or trrs jack
  // Trinket and Trinket Pro only have 1 hardware interrupt
  // so we will use pin change interrupts for them
int ditPin = 10;   // PB3
int dahPin = 11;  // PB2
int speakerPin = 9; // Digital pin 9 on Trinket pro should be high speed PWM

  // for pin change interrupts we need the following
void InitialiseInterruptTrinketPro(){
  cli();    // switch interrupts off while messing with their settings  
  PCICR =0x01;          // Enable PCINT0 interrupt
  PCMSK0 = 0b00001100; // PCINT2 + PCINT3
  sei();    // turn interrupts back on
}

PCOCommon pcoCommon(ditPin, dahPin, speakerPin);

void setup() 
{ 
  pinMode(ditPin, INPUT_PULLUP);
  pinMode(dahPin, INPUT_PULLUP);

    // Check if one of the paddle circuits is closed at startup. This is the signal
    // to enter configuration mode for either sidetone or code speed.
  pcoCommon.checkIfConfigure();

  InitialiseInterruptTrinketPro();
} 

void loop()
{
  pcoCommon.determineSymbol();
}

// Interrupt service routine. 
//Every single pin in PCMSK0: PCINT0..7 (=D8 - D13) change
// will generate an interrupt: but this will 
//always be the same interrupt routine

ISR (PCINT0_vect) {    
  if (digitalRead(ditPin)==0) { 
      pcoCommon.sendDit = true;
  } else if(digitalRead(ditPin)==1) {
      pcoCommon.sendDit = false;
  } else if (digitalRead(dahPin)==0) {
      pcoCommon.sendDah = true;
  } else if (digitalRead(dahPin)==1) {
      pcoCommon.sendDah = false;
  }
}
