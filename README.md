# MIDI Footswitch

<a href="./img/midi-2.jpg"><img src="./img/midi-2.jpg" width=220 alt="Photo of a prototype enclosed and in use" /></a>
<a href="./img/midi-1.jpg"><img src="./img/midi-1.jpg" width=370 alt="Photo of a prototype enclosed with the top of the enclosure removed" /></a>

## Description
The goal of this project is to build a device, where [a simple footswitch](https://archive.is/ykACL/2fbe0dc294888a247c4ef17947f29507e65076bb.jpg) or sustain pedal can be plugged into, and then sends a MIDI message over USB, triggered by using the pedal.

This code makes use of the Arduino library [MIDIUSB](https://github.com/arduino-libraries/MIDIUSB).

## Progress
- [x] Basic plug & play MIDI IO POC works
- [x] Reading from digital input
  - [x] Fix Debouncing
  - [x] Configuration as momentary vs switch 
- [x] Clean up the code
  - [x] Changing channel, CC number, etc should be easy to customize
- [x] Prototype a 3D printable case
  
### Future plans
- [ ] Use a stereo input jack for dual buttons
  - [ ] Bonus points for keeping the code compatible with mono jacks as well
- [ ] Design a *nice* 3D printable case
- [ ] Add schematics to this repo

## Hardware needed
- arduino board with native USB port functionality (Zero, Due, 101, Micro, Leonardo)
  - (I used a Sparkfun Pro Micro clone)
- mono or stereo 1/4inch input jack
- a simple footswitch or sustain pedal

### Wiring
Connect sleeve to ground and the tip to a pin with digital input capability. Be aware to not use a shunt contact if one is present on your jack.

<a href="./img/midi-3.jpg"><img src="./img/midi-3.jpg" width=350 alt="Photo of the prototype enclosure 3D printed and wired" /></a>

### Enclosure
[STLs](/stl/) /
[Printables](https://www.printables.com/model/449993-enclosure-for-pro-micro-quarter-inch-jack) / [Thingiverse](https://www.thingiverse.com/thing:5964743)
> Remixed from “Enclosure for DIY Ambilight with Arduino Pro Micro controller” by Florian J. aka ShreddedABS: https://www.thingiverse.com/thing:4660540

Currently this is just a rough prototype, but it works ;) (I'm currently trying to learn CAD; I may update the models in in the future)

## Configuration
The device configuration is currently hard-coded. At the top of the sketch, you can find this configuration block: 
```cpp
// Configuration ///////////////////
const bool MOMENTARY     = false; // Act as a momentary switch (true) or push button (false)
const bool INVERT        = false; // Inverts output values
                                  //
const byte MIDI_CHANNEL  = 0;     // MIDI channel 1-16, zero based
const byte MIDI_CC       = 64;    // MIDI CC number. 4 = Foot Controller; 64 = Sustain Pedal; https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2
const byte MIDI_MIN      = 0;     // MIDI value for state 'off' (0-127)
const byte MIDI_MAX      = 127;   // MIDI value for state 'on' (0-127)
                                  //
const int  INTERRUPT_PIN = 3;     // Pin number the pedal is connected to
const int  TRIGGER_LIMIT = 30;    // (Debouncing) Threshold for allowing the next trigger to occur, in milliseconds
////////////////////////////////////
```

## License
[This document](./README) and [the source code](./midi_footswitch.ino) is licensed under the [GPL v3](./LICENSE). The STL files are licensed under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).