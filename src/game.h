#pragma once

#include "game_window.h"
#include "input.h"
#include "vector.h"

#define GRID_SIZE 100

typedef struct
{
    InputState input;
    int size_x;
    int size_y;

    Square player;
    vector ennemies;

    int grid[GRID_SIZE][GRID_SIZE];
} Game;

void game_init(GameWindow* game_window, Game* game);
void game_update(GameWindow* game_window, Game* game);
void game_draw(GameWindow* game_window, Game* game);
void game_free(Game* game);

void game_add_ennemy(Game* game, Square ennemy);
void game_move_square(Game* game, Square* square, SquareType type);