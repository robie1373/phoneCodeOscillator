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
int Trinket = 1;
int Uno = 2;
int Board = Uno // Set this to the board you are running.

// CW characteristics
int sideToneFreq = 622; // should be a pleasant tone in the range CW ops are used to
int ditLength = 10;   // FIXME this is the length of a dit in milliseconds at desired WPM

// Key inputs
if (Board == Uno) {
  int ditPin = 2; // Uno 2 has hardware interrupt
  int dahPin = 3; // Uno 3 has hardware interrupt
}

if (Board == Trinket) {
  int ditPin = 3; // Trinket pin 3 has interrupt 0 attached (I hope)
  int dahPin = 4; // Trinket pin 4 has interrupt 1 attached (I hope)
}

// sound output. Can be a piezo buzzer, speaker (with amp) or 3mm trs or trrs jack
if (Board == Uno) {
  int speakerPin = 4; // Digital pin 4 on uno is basic PWM
}

if (Board == Trinket) {
  int speakerPin = 9; // Digital pin 9 on Trinket pro should be high speed PWM
}

// instantiate an oscillator (One for dits and one for dahs? TBD)
Oscillator output1(speakerPin, ditLength, sideToneFreq);

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
    // create pinchange interrupts for dit and dah pins
  }
} 

 
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
 
void loop()
{
}