# phoneCodeOscillator

This project is to create a tiny Code Oscillator / Keyer that can be plugged into the headphone jack of a smartphone. Connect a small paddle, key or cootie to the input jack and the smartphone to the output jack and you should be abble to send code into an app on your phone for practice.

## Features

* Tiny in size
* Battery powered (Trinket versions)
* Charge through micro-USB (Trinket versions)
* A second output port for monitoring with headphones
* A 8 Ohm speaker or pieze buzzer for monitoring. Switch between headphones or speaker.
* Supports Iambic or single paddle or straight key modes
* Supports a variety of sending speeds
* Has configurable sidetone pitch
* sidetone is pleasant and smooth
* Built on an Arduino clone, so the sky is the limit. Suggest a feature!

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

* Plug key into the TRS (3 conductor) headphone jack on the board. Or whatever method you choose to connect your key/paddle/pie plates.
* __It is probably a good idea to put another potentiometer or a 10k Ohm resistor between the outlet and your phone until it can be proven the levels are safe. Fair warning.__ Connect a smartphone and/or headphones to the headphone jack(s) on the board. One of the jacks is switched with the speaker, the other is always on. I bet you can figure out which is which. :)
* Power on board
* Send code!

To configure code speed __(26 Dec 2015 - Not yet implemented)__

In the meantime, this setting is in 

    phoneCodeOscillator/firmware/phoneCodeOscillatorCommon/phoneCodeOscillatorCommon.cpp
    
You can hardcode your desired settings there.

* hold the dit paddle closed while powering on the board. The reset button on the arduino works well for this.
* Once you hear the code for "ok", release the dit paddle.
* Tapping the dit paddle will raise the code speed by 1 wpm. Tapping the dah paddle will lower it by 1 wpm.
* After 2 seconds without further input the board will move into normal mode.~~

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
* update board to use switched audio jack to select between monitor headphones and speaker instead of the manual switch.
* Find a better power switch for the trinket pro

## Issues or Discussion

Please use the github issues or wiki for that.

## Announcements
* 30 December 2015 - V1.1.0 added straight key mode at the suggestion of Mr. k4hax. Circuit has been built, programmed and tested. Everything works as hoped! With respect to the volume into the phone jack, my prototype is fairly quiet. So much so in fact that I will be backing down the resistance in the output circuit. It works but is none too loud.

* 29 December 2015 - v1.0.0 is here! This code has run on a Trinket Pro and demonstrates the basic level of functionality I wanted. Huzzah! Huzzah! Huzzah! I have identified a couple of circuit revisions I want to make for quality of life reasons. Those will come in a later patch.
