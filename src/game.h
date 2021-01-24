#pragma once

#include "game_window.h"
#include "input.h"

#define SIZE_SQUARE 32
#define GRID_SIZE 100

typedef struct
{
    int x, y;
    int size;

    int direction_x;
    int direction_y;
    Color color;

} Square;

void square_draw(Square* square, GameWindow* game_window);

typedef struct
{
    InputState input;
    int size_x;
    int size_y;

    Square player;
    Square board_square[GRID_SIZE][GRID_SIZE]; 
    int board[GRID_SIZE][GRID_SIZE];
 
} Game;

void game_init(GameWindow* game_window, Game* game);
void game_update(GameWindow* game_window, Game* game);
void game_draw(GameWindow* game_window, Game* game);