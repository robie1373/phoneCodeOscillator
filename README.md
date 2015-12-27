# phoneCodeOscillator

This project is to create a tiny Code Oscillator that can be plugged into the headphone jack of a smartphone. Connect a small paddle to the input jack and the smartphone to the output jack and you should be abble to send code into an app on your phone for practice.

__Important note: I have not had a chance to build this circuit or run the code yet. This is all speculative at this point. I'll update here as I get things tested and proven. Edit: 26 Dec 2015 - The code verifies in Arduino IDE under the appropriate board at least. That's about all I can prove at this point.__

## Features

* Tiny in size
* Battery powered (Trinket versions)
* Charge through micro-USB (Trinket versions)
* (Maybe) a second output port for monitoring with headphones
* (Maybe) a pieze buzzer for monitoring
* Should support Iambic or single paddle mode
* should support a variety of sending speeds
* should have configurable sidetone pitch
* sidetone should be fairly pleasant and smooth

## Hardware designs

This repo includes designs in Fritzing for 3 versions of the board. Or will eventually. For now, all are through-hole. An SMT version would be awesome. I may do that too. Or maybe you will?

BOM will end up in the repo once stabilized.

~~26 Dec 2015 - Uno firmware officially broken for now. Something in the interrupt routine.~~

__27 Dec 2015 - Uno firmware might be fixed. I'm optimistic.__

The Uno version exists because lots of people have them already. It is less desirable because the PWM output used to generate the tone is not as high in resolution as one might want. It ought to work in a pinch, though, and if you are just running it into an app on your phone it doesn't matter at all. If you want to monitor the sidetone (as I would expect) you may get a bit tired of the sound. Who knows. With the Uno version you will be powering the circuit through the Uno. The circuit diagram does not necissarily reflect that at this point. Consider the Uno circuit to be the least well thought out. It is not my highest priority at this point frankly.

The Trinket and Trinket Pro versions are very similar. The primary difference is the pinouts of those boards. If I can design a single board to support both of them (unlikely) I will. Otherwise there will be a version for each. The trinket is quite a bitl smaller which may have advantages. Trinket and Trinket pro versions are powered by a LiPo batter running through a sweet little charging breakout board from Adafruit.

## Installing

1. clone the repo
2. create symbolic link from phoneCodeOscillator/firmware/phoneCodeOscillatorCommon/ to the Library folder in your Arduino IDE install
3. Restart Arduino IDE if needed and verify that the library shows up under Sketch -> Include Libraries...
4. If all looks good, open the version that matches your board
5. Compile and upload.

## Using

* Plug key into the TRS (3 conductor) headphone jack on the board
* Connect a smartphone and/or headphones to the TRRS (4 conductor) headphone jack(s) on the board
* Power on board
* Send code!

To configure code speed __(26 Dec 2015 - Not yet implemented)__

In the meantime, this setting is in 

    phoneCodeOscillator/firmware/phoneCodeOscillatorCommon/phoneCodeOscillatorCommon.cpp
    
You can hardcode your desired settings there.

* hold the dit paddle closed while powering on the board. The reset button on the arduino works well for this.
* Once you hear the code for "ok", release the dit paddle.
* Tapping the dit paddle will raise the code speed by 1 wpm. Tapping the dah paddle will lower it by 1 wpm.
* After 2 seconds without further input the board will move into normal mode.

To configure sidetone __(26 Dec 2015 - Not yet implemented)__

In the meantime, this setting is in 

    phoneCodeOscillator/firmware/phoneCodeOscillatorCommon/phoneCodeOscillatorCommon.cpp

You can hardcode your desired settings there.

* hold the dah paddle closed while powering on the board. The reset button on the arduino works well for this.
* Once you hear the code for "ok", release the dah paddle.
* Tapping the dit paddle will raise the sidetone by 20 hz. Tapping the dah paddle will lower it by 20 hz.
* After 2 seconds without further input the board will move into normal mode.

## Todo

* finish speed and side-tone configuration
* make speed and tone setting sticky

# Issues or Discussion

Please use the github issues or wiki for that.
