#pragma once

#include "game_window.h"

#define SIZE_SQUARE 32

typedef enum
{
    NOTHING,
    PLAYER,
    ENNEMY,
    WEIRD_SQUARE
} SquareType;

typedef struct
{
    int x, y;
    int size;
    Color color;

    int direction_x;
    int direction_y;

    int alive;
} Square;

Square square_create(int x, int y, int size, Color color, int direction_x, int direction_y);
int square_overlap(Square* s1, Square* s2);
void square_draw(Square* square, GameWindow* game_window);