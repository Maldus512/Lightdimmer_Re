/*
 * File:   newmainXC16.c
 * Author: HSW - SW Laptop
 *
 * Created on 14 aprile 2019, 18.51
 */


// PIC16F1508 Configuration Bit Settings

// 'C' source line config statements

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

#include <xc.h>


void initTimer() {
    
    OPTION_REGbits.TMR0CS = 0;  // Clock source (internal)
    OPTION_REGbits.PSA = 0; // Prescaler assignment (tmr0)
    OPTION_REGbits.PS = 0b111; // 1:256 prescaler
    /* Low Frequency internal oscillator, 31 kHz*/
    
    
//    T0CON1bits.T0CS = 0b100;
//    /* Prescaler 1:1 */
//    T0CON1bits.T0CKPS = 0b0000;
//    T0CON1bits.T0ASYNC = 1;
//    T0CON1bits.T0CKPS = 0b0000;
//    T0CON0bits.T016BIT = 0;

    /* By running 31 times the timer should be 1 ms */
    
     
    INTCONbits.T0IE = 1;
    INTCONbits.GIE = 1;
    TMR0bits.TMR0 = 0xFF - 31 + 1;
    INTCONbits.TMR0IF = 0;
    
}


void interrupt isr(void)
{
    static int count_1s = 0;
    
    if (INTCONbits.TMR0IF) {
        count_1s = 1;
        INTCONbits.TMR0IF = 0;
    } 
}


int main(void) {
    int x = 0, y;
    
    OSCCONbits.IRCF = 0b1111;
    OSCCONbits.SCS = 0b10;
    
    ANSELA = 0;
    ANSELC = 0;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC7 = 0;
    TRISCbits.TRISC6 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    TRISAbits.TRISA2 = 0;

    TRISAbits.TRISA4 = 1;
    TRISAbits.TRISA5 = 1;
    TRISCbits.TRISC5 = 1;

    
    LATCbits.LATC0 = 1; // riga verticale in alto a dx
    LATCbits.LATC1 = 1; // riga verticale in basso a dx
    LATCbits.LATC2 = 1; // riga in basso
    LATCbits.LATC3 = 1; // Common anode 1
    LATCbits.LATC4 = 0; // LED (e forse carico)
    LATCbits.LATC7 = 0; // Buzzer
    LATCbits.LATC6 = 0; // Common anode 2
    
    LATBbits.LATB4 = 0; // riga verticale in basso a sx
    LATBbits.LATB5 = 1; // riga verticale in alto a sx
    LATBbits.LATB6 = 0; // riga in mezzo
    LATBbits.LATB7 = 0; // pallino
    LATAbits.LATA2 = 1; // riga in alto
    
    LATAbits.LATA4 = 1; // Stato 1 del trimmer
    LATAbits.LATA5 = 1; // Stato 2 del trimmer
    LATCbits.LATC5 = 1; // Tasto del trimmer
    
    initTimer();
    
    while(1) {
        y = PORTAbits.RA4;
        LATCbits.LATC4 = y;
        x++;
        x--;
        y = PORTAbits.RA5;
        LATCbits.LATC0 = y;
        x++;
        x--;
        y = PORTCbits.RC5;
        LATCbits.LATC1 = y;
        x++;
        x--;
        
    }
    return 0;
}
