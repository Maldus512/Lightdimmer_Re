#ifndef __ENCODER_H__
#define __ENCODER_H__

typedef enum {
    ENCODER_NOTHING,
    ENCODER_TURN_RIGHT,
    ENCODER_TURN_LEFT,
    ENCODER_BUTTON_PRESS,
} encoder_event_t;

typedef struct {
    char last_pulse1;
    char last_pulse2;
    char last_button;
} encoder_state_t;

encoder_event_t get_encoder_event(encoder_state_t *s, char pulse1, char pulse2, char button) ;

#endif