/* MIDI Footswitch v1.0-rc1
 * https://github.com/ledeniz/midi-footswitch-converter
 *
 * Author: Deniz Erdogan
 *
 * Based on https://github.com/arduino-libraries/MIDIUSB/blob/master/examples/MIDIUSB_write/MIDIUSB_write.ino
 * Licensed under GPLv3: https://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include "MIDIUSB.h"

////////// Configuration ///////////
const bool MOMENTARY     = false; // Act as a momentary switch (true) or push button (false)
const bool INVERT        = false; // Inverts output values
                                  //
const byte MIDI_CHANNEL  = 0;     // MIDI channel 1-16, zero based
const byte MIDI_CC       = 64;    // MIDI CC number. 4 = Foot Controller; 64 = Sustain Pedal; https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2
const byte MIDI_MIN      = 0;     // MIDI value for state 'off' (0-127)
const byte MIDI_MAX      = 127;   // MIDI value for state 'on' (0-127)
                                  //
const int  INPUT_PIN     = 3;     // Pin number the jack tip is connected to
const int  DEBOUNCE_MS   = 30;    // Threshold for when to allow the next trigger, in milliseconds
////////////////////////////////////

bool state = LOW;
bool last_state = HIGH;
unsigned long state_time = 0;

bool momentary_state = HIGH;
bool momentary_latch = false;

void setup() {
  pinMode(INPUT_PIN, INPUT_PULLUP);
}

void loop() {
  state = digitalRead(INPUT_PIN);
  long unsigned t = millis();
  long unsigned delta = state_time - t;

  if (INVERT) {
    state = !state;
    momentary_state= !momentary_state;
  }

  if (delta > DEBOUNCE_MS) {
    state_time = t;

    if (state != last_state) {
      last_state = state;

      if (MOMENTARY) {
        if (!momentary_latch) {
          sendMidi(momentary_state);
          momentary_state = !momentary_state;
        }

        momentary_latch = !momentary_latch;
      } else {
        sendMidi(state);
      }
    }
  }
}

void sendMidi(bool _state) {
  if (_state) {
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
