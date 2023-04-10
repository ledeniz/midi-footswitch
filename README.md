# MIDI Footswitch
> ⚠️ Work In Progress

## Description
The goal of this project is to build a device, where [a simple footswitch](https://archive.is/ykACL/2fbe0dc294888a247c4ef17947f29507e65076bb.jpg) or sustain pedal can be plugged into, and then sends a MIDI message over USB, triggered by using the pedal.

This code makes use of the Arduino library [MIDIUSB](https://github.com/arduino-libraries/MIDIUSB).

## Progress
- [x] Basic plug & play MIDI IO POC works
- [x] Reading from digital input
  - [ ] Fix Debouncing
  - [x] Configuration as momentary vs switch 
- [x] Clean up the code
  - [x] Changing channel, CC number, etc should be easy to customize
- [ ] Design 3D printable case

## Known issues
### Bouncing
Currently the debouncing logic doesn't work well all of the time. Sometimes it can happen that a state change (pedal down/up) doesn't get recognized and then effectively the polarity of the functionality flips: up triggers like down and down triggers like up. 

## Hardware needed
- Arduino Board with native USB port functionality (Zero, Due, 101, Micro, Leonardo)
- mono 1/4inch input jack
