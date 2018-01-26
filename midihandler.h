#ifndef MIDIHANDLER_H
#define MIDIHANDLER_H

#include "mbed.h"
#include "USBMIDI.h"

void midi_write_msg(USBMIDI *midi, MIDIMessage msg);

void midi_handle_sysex(MIDIMessage msg) ;

#endif  /* MIDIHANDLER_H */