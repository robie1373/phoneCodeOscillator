class Oscillator
{
  // Class Member Variables
  // These are initialized at startup
  int outputPin;      // the number of the output pin
  long OnTime;     // milliseconds of on-time
  long Freq;    // frequency of side-tone
 
  // These maintain the current state
  volatile int outputState;                // outputState used to set the output
  volatile unsigned long previousMillis;    // will store last time output was updated
 
  // Constructor - creates a Oscillator 
  // and initializes the member variables and state
  public:
  Oscillator(int pin, long on, long freq)
  {
  outputPin = pin;
  pinMode(outputPin, OUTPUT);     
    
  OnTime = on;
  FreqTime = freq;
  
  outputState = LOW; 
  previousMillis = 0;
  }
 
  void Update(unsigned long currentMillis)
  {
    if((outputState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      outputState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(outputPin, outputState);  // Update the actual output
    }
    else if ((outputState == LOW) && (currentMillis - previousMillis >= FreqTime))
    {
      outputState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(outputPin, outputState);   // Update the actual output
    }
  }
};

// configuration switcher
int Trinket     = 1;
int TrinketPro  = 2;
int Uno         = 3;
int Board = Uno // Set this to the board you are running.

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

// Key inputs
if (Board == Uno) {
  int ditPin = 2; // Uno 2 has hardware interrupt
  int dahPin = 3; // Uno 3 has hardware interrupt
}

// Trinket and Trinket Pro only have 1 hardware interrupt
// so we will use pin change interrupts for them
if (Board == Trinket) {
  int ditPin = 1; // PB1 
  int dahPin = 2; // PB2
}

if (Board == TrinketPro) {
  int ditPin = 9;   // PB1
  int dahPin = 10;  // PB2
}

// sound output. Can be a piezo buzzer, speaker (with amp) or 3mm trs or trrs jack
if (Board == Uno) {
  int speakerPin = 4; // Digital pin 4 on uno is basic PWM
}

if (Board == Trinket) {
  int speakerPin = 0;
}

if (Board == TrinketPro) {
  int speakerPin = 9; // Digital pin 9 on Trinket pro should be high speed PWM
}

// instantiate an oscillator (One for dits and one for dahs? TBD)
Oscillator output1(speakerPin, ditLength, sideToneFreq);

// for pin change interrupts we need the following
void InitialiseInterruptTrinket(){
  cli();    // switch interrupts off while messing with their settings  
  GMSK = 0x20;          // Enable PCIE interrupt
  PCMSK = 0b00000110;  // Enable pins 
  sei();    // turn interrupts back on
}

void InitialiseInterruptTrinketPro(){
  cli();    // switch interrupts off while messing with their settings  
  PCICR =0x01;          // Enable PCINT0 interrupt
  PCMSK1 = 0b00000110;
  sei();    // turn interrupts back on
}

void setup() 
{ 
  if (Board = Uno) {
    // set up ditPin to read ditButton on regular Arduinos with 2 hardware interrups
    pinMode(ditPin, INPUT_PULLUP);
    attachInterrupt(0, PlayDit, FALLING);
    
    // set up dahPin to read dahButton on regular Arduinos with 2 hardware interrups
    pinMode(dahPin, INPUT_PULLUP);
    attachInterrupt(1, PlayDah, FALLING);
  }
  
  if (Board == Trinket) {
    InitialiseInterruptTrinket();
  
    // Interrupt service routine. 
    //Every single pin in PCMSK: PCINT0..5 (=#0 - #5) change
    // will generate an interrupt: but this will 
    //always be the same interrupt routine
  
    ISR(PCINT_vect) {    
    if (digitalRead(ditPin)==0)  Serial.println("dit");
    if (digitalRead(dahPin)==0)  Serial.println("dah");
    }
  }

  if (Board == TrinketPro) {
    InitialiseInterruptTrinketPro();
  
    // Interrupt service routine. 
    //Every single pin in PCMSK0: PCINT0..7 (=D8 - D13) change
    // will generate an interrupt: but this will 
    //always be the same interrupt routine
  
    ISR(PCINT0_vect) {    
    if (digitalRead(ditPin)==0)  Serial.println("dit");
    if (digitalRead(dahPin)==0)  Serial.println("dah");
    }
  }
} 

/* 
This is vestigial. I may need the update stuff
as a reminder for the callback to play.
Once I'm done with those I should delete this.

// Interrupt is called once a millisecond, 
SIGNAL(TIMER0_COMPA_vect) 
{
  unsigned long currentMillis = millis();
  
  // if(digitalRead(2) == HIGH)
  {
     output1.Update(currentMillis);
  }
  
  output2.Update(currentMillis);
  output3.Update(currentMillis);
} 
 */
void loop()
{
}