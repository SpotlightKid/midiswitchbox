#include "mbed.h"
#include "midiswitch.h"

SwitchHandler::SwitchHandler(EventQueue * queue, Callback<void(MIDIMessage)> cb, SwitchConfig sw) :
    queue(queue), write_cb(cb), btn(sw.pin), cfg(sw) {
    btn.mode(PullDown);
    btn.setAssertValue(1);
    btn.setSamplesTillAssert(5);
    btn.attach_asserted(callback(this, &SwitchHandler::handle_pressed));
    btn.attach_deasserted(callback(this, &SwitchHandler::handle_released));
    btn.setSampleFrequency(5000);
};

void SwitchHandler::handle_pressed(void) {
    if (cfg.on_value >= 0) {
        if (make_message(true)) {
            queue->call(write_cb, msg);
        }
    }
};

void SwitchHandler::handle_released(void) {
    if (cfg.off_value >= 0) {
        if (make_message(false)) {
            queue->call(write_cb, msg);
        }
    }
};

bool SwitchHandler::make_message(bool onoff) {
    uint8_t value = (onoff ? cfg.on_value : cfg.off_value) & 0x7F;
    msg.data[0] = CABLE_NUM | cfg.type;
    msg.data[1] = (cfg.type << 4) | (cfg.channel & 0xF);
    msg.data[2] = 0x00;
    msg.data[3] = 0x00;

    switch(cfg.type) {
        case 2:  // START
        case 3:  // CONTINUE
        case 4:  // STOP
            msg.data[0] = 0xF;
            msg.data[1] = 0xF8 + cfg.type;
            break;
        case 0xC:  // Program change
        case 0xD:  // Channel Aftertouch
            msg.data[2] = value;
            break;
        case 0x8:  // Note off
        case 0x9:  // Note on
            msg.data[3] = value;
            msg.data[2] = cfg.data1 & 0x7F;
            break;
        case 0xA:  // Poly pressure
        case 0xB:  // Control change
        case 0xE:  // PitchBend
            msg.data[2] = cfg.data1 & 0x7F;
            msg.data[3] = value;
            break;
        default:
            return false;
    }
    return true;
};
