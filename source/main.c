
 #define _XTAL_FREQ 16000000
#include <xc.h>
#include "hardwareprofile.h"
#include "state.h"
#include "system.h"
#include "digits.h"


model_t state = {0};

void interrupt isr(void)
{
    const uint16_t period = 0xFFFF - 40170;
    TMR1 = period;
    PIR1bits.TMR1IF = 0;

    LOAD = state.onoff;
}


int main(void) {
    char pulse1, pulse2, button, side;
    int counter_display = 0;
    
    OSCCONbits.IRCF = 0b1111;
    OSCCONbits.SCS = 0b10;
    
    state.onoff = 1;
        
    init_timer();
    init_gpio();
    
    while(1) {
        pulse1 = PULSE_1;
        pulse2 = PULSE_2;
        button = BUTTON;
        
        if (pulse1 != state.last_pulse_1) {
            if (state.last_pulse_2 == pulse1) {
                state.dutycycle =  state.dutycycle > 0 ? state.dutycycle - 1 : 10;
                TMR1 += 1000;
            }
            state.last_pulse_1 = pulse1;
        }
        if (pulse2 != state.last_pulse_2) {
            if (state.last_pulse_1 == pulse2) {
                state.dutycycle = (state.dutycycle + 1) % 11;
                TMR1 -= 1000;
            }
            state.last_pulse_2 = pulse2;
        }
        if (button == 0 && state.last_button == 1) {
            state.onoff = (char)!state.onoff;
        }
        state.last_button = button;
        
        if (++counter_display >= 5) {
            display_number(state.dutycycle, side);
            side = (char)!side;
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
