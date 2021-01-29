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

typedef enum
{
    RED = 3,
    VIOLET = 4,
} Frequency; 

typedef struct
{
    int x, y;
    int size;
    Color color;

    int direction_x;
    int direction_y;

    int alive;
} Square;

//Create a square
Square square_create(int x, int y, int size, Color color, int direction_x, int direction_y);
//Checking collision between 2 squares
int square_overlap(Square* s1, Square* s2);
//Drawing square
void square_draw(Square* square, GameWindow* game_window, Effect effect);