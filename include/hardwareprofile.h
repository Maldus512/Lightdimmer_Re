#ifndef __HARDWAREPROFILE_H__
#define __HARDWAREPROFILE_H__

#include <xc.h>

#define VERT_TOP_RIGHT       LATCbits.LATC0
#define VERT_BOT_RIGHT      LATCbits.LATC1
#define HORZ_BOT            LATCbits.LATC2
#define ACTIVATE_1          LATCbits.LATC3
#define ACTIVATE_2          LATCbits.LATC6
#define LOAD                LATCbits.LATC4
#define BUZZER              LATCbits.LATC7
#define VERT_BOT_LEFT       LATBbits.LATB4
#define VERT_TOP_LEFT       LATBbits.LATB5
#define HORZ_MID            LATBbits.LATB6
#define POINT               LATBbits.LATB7
#define HORZ_TOP            LATAbits.LATA2

#define VERT_TOP_RIGHT_TRIS      TRISCbits.TRISC0
#define VERT_BOT_RIGHT_TRIS      TRISCbits.TRISC1
#define HORZ_BOT_TRIS            TRISCbits.TRISC2
#define ACTIVATE_1_TRIS          TRISCbits.TRISC3
#define ACTIVATE_2_TRIS          TRISCbits.TRISC6
#define LOAD_TRIS                TRISCbits.TRISC4
#define BUZZER_TRIS              TRISCbits.TRISC7
#define VERT_BOT_LEFT_TRIS       TRISBbits.TRISB4
#define VERT_TOP_LEFT_TRIS       TRISBbits.TRISB5
#define HORZ_MID_TRIS            TRISBbits.TRISB6
#define POINT_TRIS               TRISBbits.TRISB7
#define HORZ_TOP_TRIS            TRISAbits.TRISA2
#define PULSE_1_TRIS             TRISAbits.TRISA4
#define PULSE_2_TRIS             TRISAbits.TRISA5
#define BUTTON_TRIS              TRISCbits.TRISC5

#define PULSE_1                  PORTAbits.RA4
#define PULSE_2                  PORTAbits.RA5
#define BUTTON                   PORTCbits.RC5

#endif