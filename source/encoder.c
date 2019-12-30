#include "hardwareprofile.h"
#include "encoder.h"


encoder_event_t get_encoder_event(encoder_state_t *s, char pulse1, char pulse2, char button) {    
    encoder_event_t event = ENCODER_NOTHING;
    
    if (pulse1 != s->last_pulse1 && s->last_pulse2 == pulse1) event = ENCODER_TURN_RIGHT;
    
    if (pulse2 != s->last_pulse2 && s->last_pulse1 == pulse2) event = ENCODER_TURN_LEFT;
    
    if (!button && s->last_button) event = ENCODER_BUTTON_PRESS;
    
    s->last_button = button;
    s->last_pulse1 = pulse1;
    s->last_pulse2 = pulse2;
    
    return event;
}