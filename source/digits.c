#include <stdint.h>
#include "hardwareprofile.h"


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
