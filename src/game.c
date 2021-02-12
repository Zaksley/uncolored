#include "game.h"

Color color_red = {1.0, 0.0, 0.0, 1.0};
Color color_rose = {1.0, 0, 0.66, 1.0}; 
Color color_orange = {1.0, 0.33, 0.0, 1.0}; 
Color color_white = {1.0, 1.0, 1.0, 1.0};
Color color_blue = {0.0, 0.0, 1.0, 1.0};
Color color_green = {0.0, 1.0, 0.0, 1.0};
Color color_violet = {0.45, 0.0, 0.65, 1.0};

void game_init(GameWindow* game_window, Game* game)
{
    input_state_set_window(&game->input, game_window->glfw_window);

    game->player = square_create(GRID_SIZE/2, GRID_SIZE/2, 1, color_white, 0, 0);
    game->turn = 0;
    game->ennemies_updated = 1;
    game->shake_force = 0.f;
    game->shake_time = 0.f;

    int copy_generation[COLORS] = {2, 3, 4, 5, 6, 7};
    int copy_difficulty[COLORS] = {1, 1, 2, 2, 3, 4}; 

    memcpy(game->generation, copy_generation, sizeof(int) * COLORS);
    memcpy(game->max_difficulty, copy_difficulty, sizeof(int) * COLORS);

    // Init grid
    for (int i=0; i<GRID_SIZE; i++)
    {
        for (int j=0; j<GRID_SIZE; j++)
            game->grid[i][j] = NOTHING;
    }

    vector_init(&game->ennemies, 10);

}

void game_update(GameWindow* game_window, Game* game)
{
    input_state_update(&game->input);

    if (!game->player.alive)
        return;

    int direction_x = 0;
    int direction_y = 0;

    if (is_key_released(&game->input, GLFW_KEY_RIGHT))
    {
        direction_x = 1;
    }
    else if (is_key_released(&game->input, GLFW_KEY_LEFT))
    {
        direction_x = -1;
    }
    else if (is_key_released(&game->input, GLFW_KEY_UP))
    {
        direction_y = -1;
    }
    else if (is_key_released(&game->input, GLFW_KEY_DOWN))
    {
        direction_y = 1;
    }

    if (!game->player.moving)
    {
        game->player.direction_x = direction_x;
        game->player.direction_y = direction_y;
    }

    int moved = 0;
    if ((game->player.direction_x != 0 || game->player.direction_y != 0 || game->player.moving)
        && game->ennemies_updated)
        moved = game_slide_square(game, &game->player, PLAYER, game_window->dt);

    if (moved)
    {
        game_check_ennemies_death(game);
        game_generator(game);
        game->ennemies_updated = 0;
        game->turn++;

        // Everybody start moving
        Square* ennemies = vector_at(&game->ennemies, 0);
        size_t ennemy_count = vector_size(&game->ennemies);
        for (Square* ennemy=ennemies; ennemy != ennemies + ennemy_count; ennemy++)
        {
            ennemy->moving = 1;
        }
    }

    if (!game->ennemies_updated)
    {
        int updated = 1;

        Square* ennemies = vector_at(&game->ennemies, 0);
        size_t ennemy_count = vector_size(&game->ennemies);
        for (Square* ennemy=ennemies; ennemy != ennemies + ennemy_count; ennemy++)
        {
            if (ennemy->moving && !game_update_ennemy(game, ennemy, game_window->dt))
                updated = 0;
        }

        game->ennemies_updated = updated;
    }

    // Update game shake
    game->shake_time += game_window->dt / 3.f;

    if (game->player.moving)
    {
        game->shake_time -= 1.5f * game_window->dt;

        if (game->shake_time <= 0.f)
            game->shake_time = 0.f;
    }

    game->shake_force = expf(logf(2.f + game->turn) * game->shake_time) - 1.f; //Validé: e^(4*shake_force)-1

    if (game->shake_force >= 20.f)
        game->player.alive = 0;

}

void game_draw(GameWindow* game_window, Game* game)
{
    Effect effect = no_effect();
    effect.shake = game->player.alive;
    effect.shake_force = game->shake_force;

    // Draw first ennemis
    for (size_t i=0; i<vector_size(&game->ennemies); i++)
    {
        Square* ennemy = vector_at(&game->ennemies, i);
        effect.fade = ennemy->moving;
        effect.dir_x = (float)ennemy->direction_x;
        effect.dir_y = (float)ennemy->direction_y;
        square_draw(ennemy, game_window, effect);
    }
        
    // Draw player
    effect.fade = game->player.moving;
    effect.dir_x = (float)game->player.direction_x;
    effect.dir_y = (float)game->player.direction_y;

    square_draw(&game->player, game_window, effect);
}

void game_free(Game* game)
{
    vector_free(&game->ennemies);
}

void game_add_ennemy(Game* game, Square ennemy)
{
    vector_push(&game->ennemies, ennemy);
    game->grid[ennemy.x][ennemy.y] = ENNEMY;
}

int game_update_ennemy(Game* game, Square* ennemy, float dt)
{
    // Kill player before moving
    if (square_overlap(ennemy, &game->player))
        game->player.alive = 0;

    int moved = 0;
    int next_pos_x = ennemy->x + ennemy->direction_x;
    int next_pos_y = ennemy->y + ennemy->direction_y;

    if (game->grid[next_pos_x][next_pos_y] != ENNEMY)
        moved = game_slide_square(game, ennemy, ENNEMY, dt);
    else
    {
        Square* already_here = vector_ennemy_from_pos(&game->ennemies, next_pos_x, next_pos_y); 
        already_here->alive = 0;
        moved = game_slide_square(game, ennemy, ENNEMY, dt);
    }

    // Kill player after moving 
    if (square_overlap(ennemy, &game->player))
        game->player.alive = 0;

    return moved;
}

void game_check_ennemies_death(Game* game)
{
    size_t i = 0;
    while (i < vector_size(&game->ennemies))
    {
        Square* ennemy = vector_at(&game->ennemies, i);
        if (!ennemy->alive)
            game_remove_enemy(game, i);
        else
            ++i;
    }
}

void game_remove_enemy(Game* game, size_t index)
{
    Square* ennemy = vector_at(&game->ennemies, index); 
    game->grid[ennemy->x][ennemy->y] = NOTHING;
    vector_remove(&game->ennemies, index);
}

int game_slide_square(Game* game, Square* square, SquareType type, float dt)
{
    square->move_timer += MOVE_AMOUNT;
    square->move_x += square->direction_x * SIZE_SQUARE * (MOVE_AMOUNT/SLIDE_TIME) * dt;
    square->move_y += square->direction_y * SIZE_SQUARE * (MOVE_AMOUNT/SLIDE_TIME) * dt;

    if (square->move_timer >= SLIDE_TIME)
    {
        square->move_timer = 0.f;
        square->moving = 0;

        game_move_square(game, square, type);
    }
    else square->moving = 1;

    return !square->moving;
}

void game_move_square(Game* game, Square* square, SquareType type)
{
    int next_pos_x = square->x + square->direction_x;
    int next_pos_y = square->y + square->direction_y;
    
    if (next_pos_x < 0 || next_pos_x > GRID_SIZE-1
        || next_pos_y < 0 || next_pos_y > GRID_SIZE-1)
    {
        square->alive = 0;
        return;
    }

    game->grid[square->x][square->y] = NOTHING;

    square->x = next_pos_x;
    square->move_x = next_pos_x;
    square->y = next_pos_y;
    square->move_y = next_pos_y;

    game->grid[square->x][square->y] = type;
}

void game_create_ennemy(Game *game, Color color, Frequency frequence, int dire_x[], int dire_y[])
{
    //Creation basic ennemy
    if (game->turn % frequence == 0)
    { 
        int side = rand() % 4; 
        int x = 0, y = 0;
        int direction_x = dire_x[side];
        int direction_y = dire_y[side]; 

        switch (side)
        {
            //Left
            case 0:
                x = 0;
                y = rand() % GRID_SIZE; 
                break;

            //Right
            case 1:
                x = GRID_SIZE-1;
                y = rand() % GRID_SIZE; 

                break;

            //Top
            case 2:
                x = rand() % GRID_SIZE;
                y = 0; 

                break;

            //Bottom 
            case 3:
                x = rand() % GRID_SIZE;
                y = GRID_SIZE-1; 

                break;
        }
        
        //Special comportments 
        if (color_equal(color, color_green))
        {
           int x_2, x_3, y_2, y_3; 


               //Left or right
            if (side == 0 || side == 1)
            {
               x_2 = x;
               x_3 = x;

               if (y == 0)
               {
                  y_2 = y+1;
                  y_3 = y+2; 
               }
               else if (y == GRID_SIZE-1)
               {
                  y_2 = y-1;
                  y_3 = y-2;
               }
               else
               {
                  y_2 = y-1;
                  y_3 = y+1; 
               }
            }
            
               //Bottom or Top 
            else
            {
               y_2 = y;
               y_3 = y;
               if (x == 0)
               {
                  x_2 = x+1;
                  x_3 = x+2;
               }
               else if (x == GRID_SIZE-1)
               {
                  x_2 = x-1;
                  x_3 = x-2; 
               }
               else
               {
                  x_2 = x-1;
                  x_3 = x+1; 
               }
            }

            game_add_ennemy(game, square_create(x_2, y_2, 1, color_green, direction_x, direction_y)); 
            game_add_ennemy(game, square_create(x_3, y_3, 1, color_green, direction_x, direction_y)); 

        }   

        game_add_ennemy(game, square_create(x, y, 1, color,  direction_x, direction_y));
    }
}


void game_generator(Game *game)
{
    game_update_spawning(game, game->generation, game->max_difficulty);

    int red_x[4] = {1, -1, 0, 0};
    int red_y[4] = {0, 0, 1, -1}; 
    game_create_ennemy(game, color_red, game->generation[RED], red_x, red_y); 

    int orange_x[4] = {2, -2, 0, 0};
    int orange_y[4] = {0, 0, 2, -2}; 
    game_create_ennemy(game, color_orange, game->generation[ORANGE], orange_x, orange_y); 
    
    int violet_x[4] = {1, -1, 1, -1};
    int violet_y[4] = {1, -1, 1, -1};

    game_create_ennemy(game, color_violet, game->generation[VIOLET], violet_x, violet_y);

    int rose_x[4] = {2, -2, -2, 2};
    int rose_y[4] = {-2, 2, 2, -2}; 

    game_create_ennemy(game, color_rose, game->generation[ROSE], rose_x, rose_y); 

    int blue_x[4] = {3, -3, 0, 0};
    int blue_y[4] = {0, 0, 3, -3};
    game_create_ennemy(game, color_blue, game->generation[BLUE], blue_x, blue_y); 


    game_create_ennemy(game, color_green, game->generation[GREEN], red_x, red_y); 

    // Idée: Blue = square freeze, soit se déplace à moitié, soit gèle le player 
    /*
    int blue_x[4] = {0.5, -0.5, 0, 0}; 
    int blue_y[4] = {0, 0, 0.5, -0.5}; 

    game_create_ennemy(game, color_blue, RED, blue_x, blue_y); 
    */
}


void game_update_spawning(Game *game, int generation[], int max_difficulty[])
{
    int update_turns = 10;

    if (game->turn % update_turns == 0 && game->turn != 0)
    {
        for(int i=0; i<COLORS; i++)
        {
            if (generation[i] > max_difficulty[i])
            {
                generation[i] -= 1; 
            }
        }
    }
}

Square* game_find_ennemy_by_pos(Game* game, int x, int y)
{
    Square* ennemies = vector_at(&game->ennemies, 0);
    size_t ennemy_count = vector_size(&game->ennemies);
    for (Square* ennemy=ennemies; ennemy != ennemies + ennemy_count; ennemy++)
    {
        if (ennemy->x == x && ennemy->y == y)
            return ennemy;
    }

    return NULL;
}

int color_equal(Color color_1, Color color_2)
{
    if (color_1.a != color_2.a) return 0;
    if (color_1.r != color_2.r) return 0;
    if (color_1.b != color_2.b) return 0;
    if (color_1.g != color_2.g) return 0;

    return 1; 
}