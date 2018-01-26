#include "midihandler.h"


void midi_write_msg(USBMIDI *midi, MIDIMessage msg) {
#ifndef NDEBUG
    serial->printf("Sending MIDI message controller=%d channel=%d value=%d\r\n",
                   msg.controller(), msg.channel(), msg.value());
#endif
    midi->write(msg);
}

void midi_handle_sysex(MIDIMessage msg) {
/*
    uint8_t sw;
#ifndef NDEBUG
    serial->printf("MIDI recv: header=0x%02X status=0x%02X data1=0x%02X data2=%02d length=%d\r\n",
                   msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.length);
#endif

    if (msg.data[1] == 0xF0 && msg.data[2] == 0x7D && msg.data[11] == 0xF7) {
        sw = msg.data[3];
        if (sw < NUM_SWITCHES) {
            switches[sw].type = msg.data[4] & 0xF;
            switches[sw].channel = msg.data[5] & 0xF;
            switches[sw].data1 = msg.data[6] & 0x7F;
            if (msg.data[7] > 0)
                switches[sw].on_value = msg.data[8] & 0x7F;
            else
                switches[sw].on_value = -1;
            if (msg.data[9] > 0)
                switches[sw].off_value = msg.data[10] & 0x7F;
            else
                switches[sw].off_value = -1;
            handlers[sw]->setConfig(switches[sw]);
#ifndef NDEBUG
            serial->printf("Changed configuration for switch %d.\r\n", sw + 1);
            serial->printf("type: 0x%02X\r\n", switches[sw].type);
            serial->printf("channel: %02d\r\n", switches[sw].channel);
            serial->printf("data1: %02d\r\n", switches[sw].data1);
            serial->printf("on_value: %02d\r\n", switches[sw].on_value);
            serial->printf("off_value: %02d\r\n", switches[sw].off_value);
#endif
        }
    }
*/
}


/*
// Send a Note on (pitch 42, velo 0 on channel 1)
void send_noteon() {
    led1 = LED_ON;
    midi.putc(STATUS_NOTE_ON);
    midi.putc(NOTE);
    midi.putc(127);
    led1 = LED_OFF;
}


// Send a Note off (pitch 42, velo 0 on channel 1)
void send_noteoff() {
    led1 = LED_ON;
    midi.putc(STATUS_NOTE_OFF);
    midi.putc(NOTE);
    midi.putc(0);
    led1 = LED_OFF;
}
*/
