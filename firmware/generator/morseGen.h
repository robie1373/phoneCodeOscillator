/*
PhoneCodeOscillatorCommon.h - Library of common functions for use in the board specific firmware versions. Repetition sucks.
Robie Lutsey 26 December, 2015. 
MIT license.
*/

#ifndef Morse_h
#define Morse_h

class MorseGen 
{
  public: 
    String initialize(String _input);
    void SendCode(PCOCommon _PCOCommon);

  private: 
    String _text;
    char _getNextCharacter(); 
    void _sendCharacter(char _c, PCOCommon _PCOCommon); 
};

#endif
