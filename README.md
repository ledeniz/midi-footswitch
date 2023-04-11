# MIDI Footswitch
> ⚠️ Work In Progress

## Description
The goal of this project is to build a device, where [a simple footswitch](https://archive.is/ykACL/2fbe0dc294888a247c4ef17947f29507e65076bb.jpg) or sustain pedal can be plugged into, and then sends a MIDI message over USB, triggered by using the pedal.

This code makes use of the Arduino library [MIDIUSB](https://github.com/arduino-libraries/MIDIUSB).

## Progress
- [x] Basic plug & play MIDI IO POC works
- [x] Reading from digital input
  - [x] Fix Debouncing
  - [x] Configuration as momentary vs switch 
  - [ ] Use a stereo input jack for dual buttons
- [x] Clean up the code
  - [x] Changing channel, CC number, etc should be easy to customize
  - [ ] Make code compatible for mono and stereo jack?
- [x] Prototype a 3D printable case
  - [ ] Design a nice 3D printable case

## Hardware needed
- arduino board with native USB port functionality (Zero, Due, 101, Micro, Leonardo)
  - (I used a Sparkfun Pro Micro clone)
- mono or stereo 1/4inch input jack
- a simple footswitch or sustain pedal

## Configuration
The device configuration is currently happens hard-coded. At the top of the sketch, you can find this configuration block: 
```cpp
// Configuration ///////////////////
const bool MOMENTARY     = false; // act as a momentary switch (true) or push button (false)
const bool INVERT        = false; // inverts output values
                                  //
const byte MIDI_CHANNEL  = 0;     // MIDI channel 1-16, zero based
const byte MIDI_CC       = 64;    // MIDI CC number. 4 = Foot Controller; 64 = Sustain Pedal; https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2
const byte MIDI_MIN      = 0;     // MIDI value for state 'off' (0-127)
const byte MIDI_MAX      = 127;   // MIDI value for state 'on' (0-127)
                                  //
const int  INTERRUPT_PIN = 3;     // pin number the pedal is connected to
const int  TRIGGER_LIMIT = 30;    // (debouncing) threshold for allowing the next trigger to occur, in milliseconds
////////////////////////////////////
```