
 #define _XTAL_FREQ 16000000
#include <xc.h>
#include "hardwareprofile.h"
#include "state.h"
#include "system.h"
#include "digits.h"
#include "encoder.h"


model_t state = {0};

void interrupt isr(void)
{
    const uint16_t period = 0xFFFF - 40170;
    TMR1 = period;
    PIR1bits.TMR1IF = 0;

    LOAD = state.onoff;
}


int main(void) {
    encoder_state_t enc;
    char pulse1, pulse2, button, side;
    int counter_display = 0;
    
    OSCCONbits.IRCF = 0b1111;
    OSCCONbits.SCS = 0b10;
    
    state.onoff = 0;
        
    init_timer();
    init_gpio();
    
    while(1) {
        pulse1 = PULSE_1;
        pulse2 = PULSE_2;
        button = BUTTON;
        
        switch(get_encoder_event(&enc, PULSE_1, PULSE_2, BUTTON)) {
            case ENCODER_TURN_RIGHT:
                state.counter =  state.counter > 0 ? state.counter - 1 : SNAKE_MAX - 1;
                TMR1 += 1000;
                break;
                
            case ENCODER_TURN_LEFT:
                state.counter = (state.counter + 1) % SNAKE_MAX;
                TMR1 -= 1000;
                break;
                
            case ENCODER_BUTTON_PRESS:
                state.onoff = (char)!state.onoff;
                break;
                
            case ENCODER_NOTHING:
                break;
        }
        
        if (++counter_display >= 10) {
            display_full_glyph((custom_glyph_t) state.counter, side = (char)!side);
            //display_number(state.counter, side = (char)!side);
            counter_display = 0;
        }
        
        
        if (LOAD) {
            __delay_us(10);
            LOAD = 0;
        } else {
            __delay_us(10);
        }
    }
    return 0;
}
