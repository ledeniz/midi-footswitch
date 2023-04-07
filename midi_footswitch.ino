// This was used as a starting point: https://github.com/arduino-libraries/MIDIUSB/blob/master/examples/MIDIUSB_write/MIDIUSB_write.ino

#include "MIDIUSB.h"

const byte MIDI_CHANNEL = 0;
const byte MIDI_CC = 4; // 4 = Foot Pedal; https://anotherproducer.com/online-tools-for-musicians/midi-cc-list/
const byte MIDI_MIN = 0;
const byte MIDI_MAX = 127;

int digitalInputPin = 3;
bool state = false;

unsigned long state_time = 0;
unsigned long last_state_time = 0;

////////////////////////////////////

void setup() {
  pinMode(digitalInputPin, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(digitalInputPin),
    toggleMidiCc,
    HIGH
  );
}

void toggleMidiCc() {
  state_time = millis();

  if (state_time - last_state_time < 100) { return; } // debouncing

  state = !state;

  if (state) {
    controlChange(MIDI_CHANNEL, MIDI_CC, MIDI_MAX);
  } else {
    controlChange(MIDI_CHANNEL, MIDI_CC, MIDI_MIN);
  }

  MidiUSB.flush();

  last_state_time = state_time;
}

void loop() {
  return;
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

