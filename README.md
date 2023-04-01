# MIDI Footswitch
> ⚠️ This project is not finished yet

## Description
The goal of this project is to build a device, where [a simple footswitch](https://archive.is/ykACL/2fbe0dc294888a247c4ef17947f29507e65076bb.jpg) or sustain pedal can be plugged into, and then sends a MIDI message over USB, triggered by using the pedal.

This code makes use of the Arduino library [MIDIUSB](https://github.com/arduino-libraries/MIDIUSB).

## Progress
- [x] Basic plug & play MIDI IO POC works
- [ ] Reading from digital input
  - [ ] Polarity switch during startup
  - [ ] Configuration as momentary vs switch 
- [ ] Clean up the code
  - [ ] Changing channel, CC number, etc should be easy to customize
- [ ] Design 3D printable case

---

## Hardware Needed
- Arduino Board with a Native USB port (Zero, Due, 101, Micro, Leonardo)
- mono 1/4inch input jack
