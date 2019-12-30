#ifndef __DIGITS_H__
#define __DIGITS_H__

typedef enum {
    SNAKE_1 = 0,
    SNAKE_2,
    SNAKE_3,
    SNAKE_4,
    SNAKE_5,
    SNAKE_6,
    SNAKE_7,
    SNAKE_8,
    SNAKE_MAX,
} custom_glyph_t;

typedef enum {
    SNAKE_LEFT_1,
    SNAKE_LEFT_2,
    SNAKE_LEFT_3,
    SNAKE_LEFT_4,
    SNAKE_LEFT_5,
    SNAKE_LEFT_6,
            
    SNAKE_RIGHT_1,
    SNAKE_RIGHT_2,
    SNAKE_RIGHT_3,
    SNAKE_RIGHT_4,
    SNAKE_RIGHT_5,
    SNAKE_RIGHT_6,
            
    SNAKE_EMPTY,
} half_glyph_t;

void display_number(int number, char side);
void display_full_glyph(custom_glyph_t g, char side);

#endif