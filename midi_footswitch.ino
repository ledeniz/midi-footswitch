// This was used as a starting point: https://github.com/arduino-libraries/MIDIUSB/blob/master/examples/MIDIUSB_write/MIDIUSB_write.ino

#include "MIDIUSB.h"

const byte MIDI_CHANNEL = 0;
const byte MIDI_CC = 4; // 4 = Foot Pedal; https://anotherproducer.com/online-tools-for-musicians/midi-cc-list/
const byte MIDI_MIN = 0;
const byte MIDI_MAX = 127;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  controlChange(MIDI_CHANNEL, MIDI_CC, MIDI_MAX); // Set the value of controller 10 on channel 0 to 65
  MidiUSB.flush();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);

  controlChange(MIDI_CHANNEL, MIDI_CC, MIDI_MIN); // Set the value of controller 10 on channel 0 to 65
  MidiUSB.flush();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1500);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).
void controlChange(byte channel, byte control, byte value) {

  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};

  MidiUSB.sendMIDI(event);
}

