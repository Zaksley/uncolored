#pragma once
#include "game_window.h"



typedef struct
{
    int last_state;
    int current_state;
} KeyState;

int is_key_released(KeyState state);

typedef struct
{
    int x, y;
    int size;

    int direction_x;
    int direction_y;
    Color couleur;

} Square;

typedef struct
{
    Square player;
    KeyState up_state, down_state, left_state, right_state;

    int size_x;
    int size_y;
    Square board_square[100][100]; 
    int board[100][100];
 
} Game;


void game_update(GameWindow*, Game*);
void game_draw(GameWindow*, Game*);