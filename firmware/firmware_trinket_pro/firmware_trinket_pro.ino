#include <phoneCodeOscillatorCommon.h>
#include <Encoder.h>

/* Key inputs and
 sound output. Can be a piezo buzzer, speaker (with amp) or 3mm trs or trrs jack
 Trinket and Trinket Pro only have 1 hardware interrupt
 so we will use pin change interrupts for them */
const int ditPin = 10;   // PB3
const int dahPin = 11;  // PB2
const int speakerPin = 9; // Digital pin 9 on Trinket pro should be high speed PWM
const int rotButton = 5; //
Encoder knob(3, 4);

  // for pin change interrupts we need the following
void InitialiseInterruptTrinketPro(){
  cli();    // switch interrupts off while messing with their settings  
  PCICR =0x05;          // Enable PCINT0 and PCINT2 interrupts
  PCMSK0 = 0b00001100; // PCINT2 + PCINT3
  PCMSK2 = 0b00100000; // PCINT21
  sei();    // turn interrupts back on
}

PCOCommon pcoCommon(ditPin, dahPin, speakerPin);

void setup() { 
  Serial.begin(115200);
  Serial.println("serial started");
  
  pinMode(ditPin, INPUT_PULLUP);
  pinMode(dahPin, INPUT_PULLUP);
  pinMode(rotButton, INPUT_PULLUP);

  InitialiseInterruptTrinketPro();
} 

void loop() {
  if (pcoCommon.configRequest) {
    pcoCommon.configMode();
  } else {
    pcoCommon.determineSymbol();
    }
}

// Interrupt service routine. 
// Every single pin in PCMSK0: PCINT0..7 (=D8 - D13) change
// will generate an interrupt: but this will 
// always be the same interrupt routine

ISR (PCINT0_vect) {    
   if (digitalRead(ditPin)==0) { 
      pcoCommon.sendDit = true;
  } else if(digitalRead(ditPin)==1) {
      pcoCommon.sendDit = false;
  } 

   if (digitalRead(dahPin)==0) {
      pcoCommon.sendDah = true;
  } else if (digitalRead(dahPin)==1) {
      pcoCommon.sendDah = false;
  }
}

ISR (PCINT2_vect) {
  if (digitalRead(rotButton) == LOW) {
    pcoCommon.configRequest = true;
  } else if (digitalRead(rotButton) == HIGH) {
    pcoCommon.configRequest = false;
  }
}
