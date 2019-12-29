#include "hardwareprofile.h"

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



void init_timer() {
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
