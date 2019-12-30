#include <stdint.h>
#include "hardwareprofile.h"
#include "digits.h"


static void clear_digits() {
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
}


void display_char(char c, char side) {
    clear_digits();
    
    if (side == 0) {
        ACTIVATE_1 = 1;
    } else {
        ACTIVATE_2 = 1;
    }
    
    switch(c) {
        case '0':
            VERT_BOT_LEFT = 0;
            VERT_BOT_RIGHT = 0;
            VERT_TOP_LEFT = 0;
            VERT_TOP_RIGHT = 0;
            HORZ_BOT = 0;
            HORZ_TOP = 0;
            break;
        case '1':
            VERT_BOT_RIGHT = 0;
            VERT_TOP_RIGHT = 0;
            break;
        case '2':
            VERT_TOP_RIGHT = 0;
            VERT_BOT_LEFT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;
        case '3':
            VERT_TOP_RIGHT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;
        case '4':
            VERT_TOP_RIGHT = 0;
            VERT_BOT_RIGHT = 0;
            VERT_TOP_LEFT = 0;
            HORZ_MID = 0;
            break;
        case '5':
            VERT_TOP_LEFT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;
        case '6':
            VERT_TOP_LEFT = 0;
            VERT_BOT_LEFT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;
        case '7':
            VERT_TOP_RIGHT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            break;
        case '8':
            VERT_TOP_LEFT = 0;
            VERT_TOP_RIGHT = 0;
            VERT_BOT_LEFT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;
        case '9':
            VERT_TOP_LEFT = 0;
            VERT_TOP_RIGHT = 0;
            VERT_BOT_RIGHT = 0;
            HORZ_TOP = 0;
            HORZ_BOT = 0;
            HORZ_MID = 0;
            break;            
    }
}



void display_number(int number, char side) {
    int left, right;
    left = number/10;
    right = number%10;
  
    display_char(side == 0 ? 
        (char)(left + 48) : 
        (char) (right + 48),
            side);
}

void display_half_glyph(half_glyph_t hg) {
    clear_digits();
    
    switch(hg) {
        case SNAKE_LEFT_1:
            ACTIVATE_1 = 1;
            HORZ_BOT = 0;
            break;
            
        case SNAKE_LEFT_2:
            ACTIVATE_1 = 1;
            HORZ_BOT = 0;
            VERT_BOT_LEFT = 0;
            break;
            
        case SNAKE_LEFT_3:
            ACTIVATE_1 = 1;
            HORZ_BOT = 0;
            VERT_BOT_LEFT = 0;
            VERT_TOP_LEFT = 0;
            break;
            
        case SNAKE_LEFT_4:
            ACTIVATE_1 = 1;
            VERT_BOT_LEFT = 0;
            VERT_TOP_LEFT = 0;
            HORZ_TOP = 0;
            break;
            
        case SNAKE_LEFT_5:
            ACTIVATE_1 = 1;
            VERT_TOP_LEFT = 0;
            HORZ_TOP = 0;
            break;
            
        case SNAKE_LEFT_6:
            ACTIVATE_1 = 1;
            HORZ_TOP = 0;
            break;
            
        case SNAKE_RIGHT_1:
            ACTIVATE_2 = 1;
            HORZ_TOP = 0;
            break;
            
        case SNAKE_RIGHT_2:
            ACTIVATE_2 = 1;
            HORZ_TOP = 0;
            VERT_TOP_RIGHT = 0;
            break;
            
        case SNAKE_RIGHT_3:
            ACTIVATE_2 = 1;
            HORZ_TOP = 0;
            VERT_BOT_RIGHT = 0;
            VERT_TOP_RIGHT = 0;
            break;
            
        case SNAKE_RIGHT_4:
            ACTIVATE_2 = 1;
            VERT_BOT_RIGHT = 0;
            VERT_TOP_RIGHT = 0;
            HORZ_BOT = 0;
            break;
            
        case SNAKE_RIGHT_5:
            ACTIVATE_2 = 1;
            VERT_BOT_RIGHT = 0;
            HORZ_BOT = 0;
            break;
            
        case SNAKE_RIGHT_6:
            ACTIVATE_2 = 1;
            HORZ_BOT = 0;
            break;
            
        case SNAKE_EMPTY:
            break;
    }
}

void display_full_glyph(custom_glyph_t g, char side) {
    half_glyph_t hf;
    
    switch(g) {
        case SNAKE_1:
            hf = side == 0 ? SNAKE_LEFT_1 : SNAKE_RIGHT_5;
            break;
            
        case SNAKE_2:
            hf = side == 0 ? SNAKE_LEFT_2 : SNAKE_RIGHT_6;
            break;
            
        case SNAKE_3:
            hf = side == 0 ? SNAKE_LEFT_3 : SNAKE_EMPTY;
            break;
            
        case SNAKE_4:
            hf = side == 0 ? SNAKE_LEFT_4 : SNAKE_EMPTY;
            break;
            
        case SNAKE_5:
            hf = side == 0 ? SNAKE_LEFT_5 : SNAKE_RIGHT_1;
            break;
            
        case SNAKE_6:
            hf = side == 0 ? SNAKE_LEFT_6 : SNAKE_RIGHT_2;
            break;
            
        case SNAKE_7:
            hf = side == 0 ? SNAKE_EMPTY : SNAKE_RIGHT_3;
            break;
            
        case SNAKE_8:
            hf = side == 0 ? SNAKE_EMPTY : SNAKE_RIGHT_4;
            break;
            
    }
    
    display_half_glyph(hf);
}