// MIDI Footswitch
// https://github.com/ledeniz/midi-footswitch
//
// Based on https://github.com/arduino-libraries/MIDIUSB/blob/master/examples/MIDIUSB_write/MIDIUSB_write.ino

#include "MIDIUSB.h"

// Configuration ////////////////////
const bool MOMENTARY     = false; // act as a momentary switch (true) or push button (false)
                                  //
const byte MIDI_CHANNEL  = 0;     // MIDI channel 1-16, zero based
const byte MIDI_CC       = 64;    // MIDI CC number. 4 = Foot Controller; 64 = Sustain Pedal; https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2
const byte MIDI_MIN      = 0;     // MIDI value for state 'off' (0-127)
const byte MIDI_MAX      = 127;   // MIDI value for state 'on' (0-127)
                                  //
const int  INTERRUPT_PIN = 3;     // pin number the pedal is connected to
const int  TRIGGER_LIMIT = 250;   // (debouncing) threshold for allowing the next trigger to occur, in milliseconds
////////////////////////////////////

bool state = false;
bool last_state = false;
unsigned long state_time = 0;
unsigned long last_state_time = 0;
bool momentary_latch = false;

////////////////////////////////////

void setup() {
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(INTERRUPT_PIN),
    buttonInterrupt,
    CHANGE
  );
}

void buttonInterrupt() {
  state_time = millis();

  if (state_time - last_state_time < TRIGGER_LIMIT) { return; } // ignore interrupt if below threshold
  last_state_time = state_time;

  if (MOMENTARY && momentary_latch) { momentary_latch = false; return; } // momentary logic: if latched, ignore event but unlatch
  momentary_latch = true;

  state = !state;
}

////////////////////////////////////

void loop() { 
  if (state != last_state) {
    last_state = state;
    sendMidi();
  }
}

void sendMidi() {
  if (state) {
    sendControlChange(MIDI_CHANNEL, MIDI_CC, MIDI_MAX);
  } else {
    sendControlChange(MIDI_CHANNEL, MIDI_CC, MIDI_MIN);
  }

  MidiUSB.flush();
}

// `channel` - midi channel number (0-15)
// `control` - control function number (0-119)
// `value`   - value for control function (0-127)
void sendControlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
