#ifndef __STATE_H__
#define __STATE_H__
#include <stdint.h>

typedef struct {
    int dutycycle;
    char onoff;
    uint8_t last_pulse_1, last_pulse_2;
    uint8_t last_button;
} model_t;

#endif