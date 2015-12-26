  // Key inputs and
  // sound output. Can be a piezo buzzer, speaker (with amp) or 3mm trs or trrs jack
  // Trinket and Trinket Pro only have 1 hardware interrupt
  // so we will use pin change interrupts for them
int ditPin = 1; // PB1 
int dahPin = 2; // PB2
int speakerPin = 0;

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
boolean last;
unsigned long now;
unsigned long interToneLockTimer;

  // for pin change interrupts we need the following
void InitialiseInterruptTrinket(){
  cli();    // switch interrupts off while messing with their settings  
  GMSK = 0x20;          // Enable PCIE interrupt
  PCMSK = 0b00000110;  // Enable pins 
  sei();    // turn interrupts back on
}

void playDit() {
  now = millis();
  if (now > interToneLockTimer) {
    tone(speakerPin, sideToneFreq, ditLength);
  }
  interToneLockTimer = millis() + interToneLength;
  last = dit;
}

void playDah() {
  now = millis();
  if (now > interToneLockTimer) {
    tone(speakerPin, sideToneFreq, dahLength);
  }
  interToneLockTimer = millis() + interToneLength;
  last = dah;
}

void play(sym) {
  if (sym) {
    playDit();
  } else {
    playDah();
  } 
}

void diDah() {
  if (digitalRead(ditPin)==0 && digitalRead(dahPin)==0) {
    play(!last);
    pause();  // FIXME. How are you going to handle the timing
              // between this pause and the lock in play()?
  }
}

void setup() 
{ 
  pinMode(ditPin, INPUTPULLUP);
  pinMode(dahPin, INPUTPULLUP);

  InitialiseInterruptTrinket();

  // Interrupt service routine. 
  //Every single pin in PCMSK: PCINT0..5 (=#0 - #5) change
  // will generate an interrupt: but this will 
  //always be the same interrupt routine

  ISR(PCINT_vect) {    
    if (iambic) {
      diDah(); // pin detection built into diDah()
    } else if {
      (digitalRead(ditPin)==0)  play(dit);
    } else if {
      (digitalRead(dahPin)==0)  play(dah);
    }
  }
} 

void loop()
{
}