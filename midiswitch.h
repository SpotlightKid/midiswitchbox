#ifndef MIDISWITCH_H
#define MIDISWITCH_H

#include "mbed.h"
#include "mbed_events.h"
#include "PinDetect.h"
#include "USBMIDI.h"


typedef struct SwitchConfig {
    PinName pin;
    uint8_t type;
    uint8_t channel;
    uint8_t data1;
    int8_t on_value;
    int8_t off_value;
} SwitchConfig;

typedef void (*MIDI_CB)(MIDIMessage);

class SwitchHandler {
public:
    SwitchHandler(EventQueue * queue, Callback<void(MIDIMessage)> cb, SwitchConfig sw);
    void handle_pressed(void);
    void handle_released(void);
    void setConfig(SwitchConfig sw) {
        cfg = sw;
    };
private:
    bool make_message(bool onoff);
    EventQueue * queue;
    Callback<void(MIDIMessage)> write_cb;
    PinDetect btn;
    SwitchConfig cfg;
    MIDIMessage msg;
};

#endif  /* MIDISWITCH_H */
