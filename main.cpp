#include "config.h"
#include "mbed.h"
#include "mbed_events.h"
#include "PinDetect.h"
#include "midiswitch.h"
#include "midihandler.h"

/* ******************** Configuration ***************************** */

#define MIDI_BAUDRATE 31250
#define LED_ON 0
#define LED_OFF 1

/* ******************** End Configuration ************************* */

#ifndef NDEBUG
Serial *serial;
#endif
USBMIDI * midi;
/* array of pointers to SwitchHandler instances */
SwitchHandler * handlers[NUM_SWITCHES];

// create an event queue
EventQueue queue;

// create a thread that'll run the event queue's dispatch function
Thread midiThread;

DigitalOut led1(LED1);
PinDetect btn(PB_4, PullDown);
//RawSerial midi(PA_9, PA_10, MIDI_BAUDRATE);

void usbmidi_send(MIDIMessage msg) {
    midi_write_msg(midi, msg);
}

int main() {
    led1 = LED_OFF;

#ifndef NDEBUG
    serial->printf("Creating USBMIDI device...\r\n");
#endif
    midi = new USBMIDI(0x1f00, 0x2012, 0x0001);

#ifndef NDEBUG
    serial->printf("Starting event queue thread...\r\n");
#endif
    midiThread.start(callback(&queue, &EventQueue::dispatch_forever));

    for (int sw=0; sw < NUM_SWITCHES; sw++) {
#ifndef NDEBUG
        serial->printf("Initializing switch handler %d...\r\n", sw + 1);
#endif
        handlers[sw] = new SwitchHandler(&queue, usbmidi_send, switches[sw]);
    }

    midi->attach(&midi_handle_sysex);

#ifndef NDEBUG
    serial->printf("Entering main loop...\r\n");
#endif
    while (true) {}
}
