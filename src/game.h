#pragma once

#include "game_window.h"
#include "input.h"
#include "vector.h"
#include "math.h"

#define GRID_SIZE 20
#define COLORS 6

typedef struct
{
    InputState input;

    int turn;  
    Square player;

    int generation[COLORS];
    int max_difficulty[COLORS];

    float shake_time;
    float shake_force;

    int ennemies_updated;
    vector ennemies;

    int grid[GRID_SIZE][GRID_SIZE];
} Game;

void game_init(GameWindow* game_window, Game* game);
void game_update(GameWindow* game_window, Game* game);
void game_draw(GameWindow* game_window, Game* game);
void game_free(Game* game);

void game_add_ennemy(Game* game, Square ennemy);
int game_update_ennemy(Game* game, Square* ennemy, float dt);
void game_update_spawning(Game* game, int generation[], int max_difficulty[]);
void game_check_ennemies_death(Game* game);
void game_remove_enemy(Game* game, size_t index);
int game_slide_square(Game* game, Square* square, SquareType type, float dt);
void game_move_square(Game* game, Square* square, SquareType type);
void game_generator(Game* game); 
void game_create_ennemy(Game* game, Color color, int rank, Frequency frequence, int dire_x[], int dire_y[]);

Square* find_ennemy_by_pos(Game* game, int x, int y);

int color_equal(Color color_1, Color color_2);