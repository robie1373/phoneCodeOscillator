# Generator libraries for phoneCodeOscillator.

These are the libraries used when you want to use PCO to translate ascii text to CW. Depending on the configuration of your device and your goals you might save text files to the SD card, translate text received over serial, WiFi, or Bluetooth, or text to speach. You've got a great-bit uProcessor there, so the sky's the limit.

## Usage

First call 

    MorseGen::initialize(String _input) 

to initialize the instance with your string. In most cases, you'll have tons of memory in your uProcessor to store long strings. Probably not War and Peace, but certianly enough for the most common 100 words for example. If, however, you find yourself short on memory you could just initialize a MorseGen for each sentence, or line or whatever. My understanding of grabace collection is that the old instance will be collected once they are no longer referenced. I.E. after you are done with them in your loop, and start working on a new sentence.

Then call 

    MorseGen::SendCode(PCOCommon _PCOCommon) 

to actually send your CW. You must pass SendCode your instance of PCOCommon so it has access to sendDit and sendDah.
