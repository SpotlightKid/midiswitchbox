#ifndef CONFIG_H
#define CONFIG_H

#include "midiswitch.h"

#define NUM_SWITCHES 2

/* array of SwitchConfig structs */
SwitchConfig switches[NUM_SWITCHES] = {
    // pin, type, channel, data1, on_value, off_value
    {PB_4, 0xB, 0, 1, 127, 0},
    {PB_5, 0xC, 0, 0, 1, -1},
};


#endif  /* CONFIG_H */