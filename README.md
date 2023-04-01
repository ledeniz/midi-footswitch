# MIDI Footswitch
> ⚠️ This project is not finished yet

## Description
The goal of this project is to build a plug&play device, where [a simple footswitch pedal](https://archive.is/ykACL/2fbe0dc294888a247c4ef17947f29507e65076bb.jpg) or sustain pedal can be plugged into, and then sends a MIDI message triggered by using the pedal over USB MIDI.

, that connects to a mono 1/4 inch jack (something like ).


This code makes use of the Arduino library [MIDIUSB](https://github.com/arduino-libraries/MIDIUSB).

## Progress
- [x] Basic MIDI IO POC works 
- [ ] Reading from digital input
  - [ ] Polarity switch during startup
- [ ] Clean up the code
  - [ ] Changing channel, CC number, etc should be easy to customize
- [ ] Design 3D printable case

---

## Hardware Needed
- Arduino Board with a Native USB port (Zero, Due, 101, Micro, Leonardo)
- mono 1/4inch input jack
