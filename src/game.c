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

    game->player = square_create(0, 0, 1, color_white, 0, 0);
    game->turn = 0;
    game->ennemies_updated = 1;

    // Init grid
    for (int i=0; i<GRID_SIZE; i++)
    {
        for (int j=0; j<GRID_SIZE; j++)
            game->grid[i][j] = NOTHING;
    }

    vector_init(&game->ennemies, 10);

    game_add_ennemy(game, square_create(15, 7, 1, color_red, -1, 0));
    game_add_ennemy(game, square_create(15, 5, 1, color_red, 1, 1));
    game_add_ennemy(game, square_create(10, 10, 1, color_red, 0, -1));
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
        game_generator(game);
        game->ennemies_updated = 0;

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
    else
    {
        game_check_ennemies_death(game);
        game->turn++;
    }
}

void game_draw(GameWindow* game_window, Game* game)
{
    Effect effect = no_effect();

    if (!game->player.moving)
        effect.shake = 1;

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
    effect = no_effect();

    if (game->player.moving)
    {
        effect.fade = 1;
        effect.dir_x = (float)game->player.direction_x;
        effect.dir_y = (float)game->player.direction_y;
    }
    else effect.shake = 1;

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
    //TODO Gérez collisions ennemis 
    else
    {
        ennemy->alive = 0;
        return 1;
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
        
        game_add_ennemy(game, square_create(x, y, 1, color, direction_x, direction_y));
    }
}


void game_generator(Game *game)
{
    int red_x[4] = {1, -1, 0, 0};
    int red_y[4] = {0, 0, 1, -1}; 
    game_create_ennemy(game, color_red, RED, red_x, red_y); 

    int orange_x[4] = {2, -2, 0, 0};
    int orange_y[4] = {0, 0, 2, -2}; 
    game_create_ennemy(game, color_orange, ORANGE, orange_x, orange_y); 
    
    int violet_x[4] = {1, -1, 1, -1};
    int violet_y[4] = {1, -1, 1, -1};

    game_create_ennemy(game, color_violet, VIOLET, violet_x, violet_y);

    int rose_x[4] = {2, -2, -2, 2};
    int rose_y[4] = {-2, 2, 2, -2}; 

    game_create_ennemy(game, color_rose, ROSE, rose_x, rose_y); 


        // Idée: Blue = square freeze, soit se déplace à moitié, soit gèle le player 
    /*
    int blue_x[4] = {0.5, -0.5, 0, 0}; 
    int blue_y[4] = {0, 0, 0.5, -0.5}; 

    game_create_ennemy(game, color_blue, RED, blue_x, blue_y); 
    */
}