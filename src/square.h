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
} Square;

void square_draw(Square* square, GameWindow* game_window);