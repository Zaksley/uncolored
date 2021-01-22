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
} Square;

typedef struct
{
    Square player;
    KeyState up_state, down_state, left_state, right_state;
} Game;

void game_update(GameWindow*, Game*);
void game_draw(GameWindow*, Game*);