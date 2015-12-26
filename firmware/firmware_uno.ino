  // Key inputs and
  // sound output. Can be a piezo buzzer, speaker (with amp) or 3mm trs or trrs jack
int ditPin = 2; // Uno 2 has hardware interrupt
int dahPin = 3; // Uno 3 has hardware interrupt
int speakerPin = 5; // Digital pin 5 on uno is basic PWM

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

void play() {
  if (!last) {
    playDit();
  } else {
    playDah();
  } 
}

void pause() {
  
}

void diDah() {
  if (digitalRead(ditPin)==0 && digitalRead(dahPin)==0) {
    play();
    pause();  // FIXME. How are you going to handle the timing
              // between this pause and the lock in play()?
  }
}

void setup() 
{ 

  // set up ditPin to read ditButton on regular Arduinos with 2 hardware interrups
  pinMode(ditPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(0), playDit, LOW);
  
  // set up dahPin to read dahButton on regular Arduinos with 2 hardware interrups
  pinMode(dahPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(1), playDah, LOW);
} 

void loop()
{
}