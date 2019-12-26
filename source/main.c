// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
 #define _XTAL_FREQ 16000000
#include <xc.h>
#include "hardwareprofile.h"
#include "state.h"

model_t state = {0};


void display_number(int number, uint8_t side) {
    int left, right, todisplay;
    left = number/10;
    right = number%10;
    
    VERT_BOT_LEFT = 1;
    VERT_BOT_RIGHT = 1;
    VERT_TOP_LEFT = 1;
    VERT_TOP_RIGHT = 1;
    HORZ_BOT = 1;
    HORZ_MID = 1;
    HORZ_TOP = 1;
    POINT = 1;
    ACTIVATE_1 = 0;
    ACTIVATE_2 = 0;
    
    if (side == 0) {
        ACTIVATE_1 = 1;
        todisplay = left;
    } else {
        ACTIVATE_2 = 1;
        todisplay = right;
    }
    
    switch(todisplay) {
        case 0:
            VERT_BOT_LEFT = 0;
            VERT_BOT_RIGHT = 0;
            VERT_TOP_LEFT = 0;
            VERT_TOP_RIGHT = 0;
            HORZ_BOT = 0;
            HORZ_TOP = 0;
            break;
        case 1:
            VERT_BOT_RIGHT = 0;
            VERT_TOP_RIGHT = 0;
            break;
        case 2:
            VERT_TOP_RIGHT = 0;
            VERT_BOT_LEFT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;
        case 3:
            VERT_TOP_RIGHT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;
        case 4:
            VERT_TOP_RIGHT = 0;
            VERT_BOT_RIGHT = 0;
            VERT_TOP_LEFT = 0;
            HORZ_MID = 0;
            break;
        case 5:
            VERT_TOP_LEFT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;
        case 6:
            VERT_TOP_LEFT = 0;
            VERT_BOT_LEFT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;
        case 7:
            VERT_TOP_RIGHT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            break;
        case 8:
            VERT_TOP_LEFT = 0;
            VERT_TOP_RIGHT = 0;
            VERT_BOT_LEFT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;
        case 9:
            VERT_TOP_LEFT = 0;
            VERT_TOP_RIGHT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;            
    }
    
}

void initTimer() {
    T1CONbits.TMR1ON = 1;
    T1GCONbits.TMR1GE = 0;
    T1CONbits.TMR1CS = 0; // TMR1 source is FOSC/4 (instruction frequency)
    T1CONbits.T1CKPS = 0; // 1:1 prescaler
    T1GCONbits.T1GSS = 0;
    PIE1bits.TMR1IE = 1;
    PIR1bits.TMR1IF = 0;
    INTCONbits.PEIE = 1;
    
    INTCONbits.GIE = 1;
}

void init_gpio() {
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    
    VERT_BOT_LEFT_TRIS = 0;
    VERT_BOT_RIGHT_TRIS = 0;
    VERT_TOP_LEFT_TRIS = 0;
    VERT_TOP_RIGHT_TRIS = 0;
    HORZ_BOT_TRIS = 0;
    HORZ_MID_TRIS = 0;
    HORZ_TOP_TRIS = 0;
    POINT_TRIS = 0;
    LOAD_TRIS = 0;
    BUZZER_TRIS = 0;
    ACTIVATE_1_TRIS = 0;
    ACTIVATE_2_TRIS = 0;
    
    PULSE_1_TRIS = 1;
    PULSE_2_TRIS = 1;
    BUTTON_TRIS = 1;
}

uint8_t  counter_ac = 0;
static int counter_display = 0;
static uint8_t side = 0;

const uint16_t period = 0xFFFF - 40170;

void interrupt isr(void)
{
    TMR1 = period;
    PIR1bits.TMR1IF = 0;

    LOAD = state.onoff;
}


int main(void) {
    uint8_t pulse1, pulse2, button;
    
    OSCCONbits.IRCF = 0b1111;
    OSCCONbits.SCS = 0b10;
    
    state.onoff = 1;
        
    unsigned long counter = 0;
    initTimer();
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
            state.onoff = 1-state.onoff;
        }
        state.last_button = button;
        
        if (++counter_display >= 5) {
            display_number(state.dutycycle, side);
            side = 1 - side;
            counter_display = 0;
        }
        
        
        if (LOAD) {
            __delay_us(10);
            LOAD = 0;
        } else {
            __delay_us(10);
        }
        counter++;
    }
    return 0;
}
