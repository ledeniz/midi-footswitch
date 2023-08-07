/* MIDI Footswitch Converter v1.1
 * https://github.com/ledeniz/midi-footswitch-converter
 *
 * Author: Deniz Erdogan
 *
 * Based on https://github.com/arduino-libraries/MIDIUSB/blob/master/examples/MIDIUSB_write/MIDIUSB_write.ino
 * Licensed under GPLv3: https://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include "MIDIUSB.h"

#define MODE_CC   1
#define MODE_NOTE 2

//////// Configuration section 
// CC mode:   `MODE = MODE_CC` 
// Note mode: `MODE = MODE_NOTE`
// Both:      `MODE = MODE_CC | NOTE_NOTE`
const unsigned short MODE = MODE_NOTE; 

// Act as a momentary switch (false) or toggle switch (true)
const bool TOGGLE = false;
// Inverts output values
const bool INVERT = false;

// MIDI channel 1-16, zero based
const byte MIDI_CHANNEL = 0;

// MIDI CC number. 4 = Foot Controller; 64 = Sustain Pedal
// https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2
const byte MIDI_CC = 64;
// MIDI value for state 'off' (0-127)
const byte MIDI_CC_MIN = 0;
// MIDI value for state 'on' (0-127)
const byte MIDI_CC_MAX = 127;

// MIDI note pitch value (0-127; 48 = middle C)
const byte MIDI_NOTE = 48;
// MIDI note velocity value (64 = normal, 127 = fastest)
const byte MIDI_NOTE_VELOCITY = 100;

// Pin number the jack tip is connected to
const int  INPUT_PIN = 3;
// Threshold for when to allow the next trigger, in milliseconds
const int  DEBOUNCE_MS = 30;

//////// END of Configuration section

bool state = LOW;
bool last_state = HIGH;
unsigned long state_time = 0;

bool toggle_state = HIGH;
bool toggle_latch = true;

void setup() {
  pinMode(INPUT_PIN, INPUT_PULLUP);
}

void loop() {
  state = digitalRead(INPUT_PIN);
  long unsigned t = millis();
  long unsigned delta = state_time - t;

  if (delta > DEBOUNCE_MS) {
    state_time = t;

    if (state != last_state) {
      last_state = state;

    if (INVERT) {
      state = !state;
      toggle_state= !toggle_state;
    }

      if (TOGGLE) {
        if (!toggle_latch) {
          sendMidi(toggle_state);
          toggle_state = !toggle_state;
        }

        toggle_latch = !toggle_latch;
      } else {
        sendMidi(state);
      }
    }
  }
}

void sendMidi(bool _state) {
  if (_state) {
    if (MODE & MODE_CC) {
      sendControlChange(MIDI_CHANNEL, MIDI_CC, MIDI_CC_MAX);
    }

    if (MODE & MODE_NOTE) {
      sendNoteOn(MIDI_CHANNEL, MIDI_NOTE, MIDI_NOTE_VELOCITY);
    }
  } else {
    if (MODE & MODE_CC) {
      sendControlChange(MIDI_CHANNEL, MIDI_CC, MIDI_CC_MIN);
    }

    if (MODE & MODE_NOTE) {
      sendNoteOff(MIDI_CHANNEL, MIDI_NOTE, MIDI_NOTE_VELOCITY);
    }
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

// `channel`  - midi channel number (0-15)
// `pitch`    - note number (0-127)
// `velocity` - 64 = normal, 127 = fastest
void sendNoteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

// `channel`  - midi channel number (0-15)
// `pitch`    - note number (0-127)
// `velocity` - 64 = normal, 127 = fastest
void sendNoteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
