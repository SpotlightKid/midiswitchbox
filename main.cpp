#include "mbed.h"
#include "mbed_events.h"
#include "PinDetect.h"

#define MIDI_BAUDRATE 31250
#define STATUS_NOTE_OFF 0x80
#define STATUS_NOTE_ON 0x90
#define NOTE 48
#define LED_ON 0
#define LED_OFF 1


// create an event queue
EventQueue queue;

// create a thread that'll run the event queue's dispatch function
Thread eventThread;

DigitalOut led1(LED1);
PinDetect btn(PB_4, PullDown);
RawSerial midi(PA_9, PA_10, MIDI_BAUDRATE);


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


int main() {
    led1 = LED_OFF;
    eventThread.start(callback(&queue, &EventQueue::dispatch_forever));

    btn.setAssertValue(1);
    btn.setSamplesTillAssert(5);
    // wrap calls in queue.event to run callbacks in queue's thread context
    btn.attach_asserted(queue.event(send_noteon));
    btn.attach_deasserted(queue.event(send_noteoff));
    // start pulling button pin
    btn.setSampleFrequency(5000);

    while (true) {}
}
