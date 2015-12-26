# phoneCodeOscillator

This project is to create a tiny Code Oscillator that can be plugged into the headphone jack of a smartphone. Connect a small paddle to the input jack and the smartphone to the output jack and you should be abble to send code into an app on your phone for practice.

__Important note: I have not had a chance to build this circuit or run the code yet. This is all speculative at this point. I'll update here as I get things tested and proven.__

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

This repo includes designs for 3 versions of the board. Or will eventually. For now, all are through-hole. An SMT version would be awesome. I may do that too. Or maybe you will?

BOM will end up in the repo once stabilized.

The Uno version exists because lots of people have them already. It is less desirable because the PWM output used to generate the tone is not as high in resolution as one might want. It ought to work in a pinch, though, and if you are just running it into an app on your phone it doesn't matter at all. If you want to monitor the sidetone (as I would expect) you may get a bit tired of the sound. Who knows. With the Uno version you will be powering the circuit through the Uno. The circuit diagram does not necissarily reflect that at this point. Consider the Uno circuit to be the least well thought out. It is not my highest priority at this point frankly.

The Trinket and Trinket Pro versions are very similar. The primary difference is the pinouts of those boards. If I can design a single board to support both of them (unlikely) I will. Otherwise there will be a version for each. The trinket is quite a bitl smaller which may have advantages. Trinket and Trinket pro versions are powered by a LiPo batter running through a sweet little charging breakout board from Adafruit.