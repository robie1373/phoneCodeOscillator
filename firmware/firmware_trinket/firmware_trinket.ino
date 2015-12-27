#include <phoneCodeOscillatorCommon.h>


  // Key inputs and
  // sound output. Can be a piezo buzzer, speaker (with amp) or 3mm trs or trrs jack
  // Trinket and Trinket Pro only have 1 hardware interrupt
  // so we will use pin change interrupts for them
int ditPin = 1; // PB1 
int dahPin = 2; // PB2
int speakerPin = 0;

  // for pin change interrupts we need the following
void InitialiseInterruptTrinket(){
  cli();    // switch interrupts off while messing with their settings  
  GIMSK =   0b00010000;  // Enable PCIE interrupt
  PCMSK  =  0b00000110;  // Enable pins 
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

  InitialiseInterruptTrinket();

} 

void loop()
{
}

// Interrupt service routine. 
//Every single pin in PCMSK: PCINT0..5 (=#0 - #5) change
// will generate an interrupt: but this will 
//always be the same interrupt routine

ISR(PCINT_vect) {    
  if (pcoCommon.iambic) {
    // pin detection built into diDah()
    pcoCommon.diDah(); 
  } else if (digitalRead(ditPin)==0) { 
      pcoCommon.play(pcoCommon.dit);
  } else if (digitalRead(dahPin)==0) {
      pcoCommon.play(pcoCommon.dah);
  }
}
