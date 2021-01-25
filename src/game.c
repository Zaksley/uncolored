#include "game.h"

Color color_red = {1.0, 0.0, 0.0, 1.0};
Color color_white = {1.0, 1.0, 1.0, 1.0};
Color color_blue = {0.0, 0.0, 1.0, 1.0};
Color color_green = {0.0, 1.0, 0.0, 1.0};
Color color_violet = {0.75, 0.0, 0.75, 1.0}; 

void game_init(GameWindow* game_window, Game* game)
{
    input_state_set_window(&game->input, game_window->glfw_window);
 
    game->player = square_create(0, 0, 1, color_white, 0, 0);

    game->size_x = GRID_SIZE;
    game->size_y = GRID_SIZE;

    // Init grid
    for (int i=0; i<game->size_x; i++)
    {
        for (int j=0; j<game->size_y; j++)
            game->grid[i][j] = NOTHING; 
    }

    vector_init(&game->ennemies, 10);

    game_add_ennemy(game, square_create(15, 5, 1, color_red, -1, 0));
    game_add_ennemy(game, square_create(15, 5, 1, color_red, 1, 1));
    game_add_ennemy(game, square_create(10, 10, 1, color_red, 0, -1));
}

void game_update(GameWindow* game_window, Game* game)
{
    input_state_update(&game->input);

    if (!game->player.alive)
        return;

    int moved = 0;
    game->player.direction_x = 0;
    game->player.direction_y = 0;

    if (is_key_released(&game->input, GLFW_KEY_RIGHT))
    {
        game->player.direction_x = 1;
    }
    else if (is_key_released(&game->input, GLFW_KEY_LEFT))
    {
        game->player.direction_x = -1; 
    }
    else if (is_key_released(&game->input, GLFW_KEY_UP))
    {
        game->player.direction_y = -1;
    }
    else if (is_key_released(&game->input, GLFW_KEY_DOWN))
    {
        game->player.direction_y = 1;
    }

    if (game->player.direction_x != 0 || game->player.direction_y != 0)
    {
        game_move_square(game, &game->player, PLAYER);
        moved = 1; 
    }

    //TODO Fonction qui check si y'avait pas déjà quelque chose =>>> Mort du player

    if (moved)
    {
        Square* ennemies = vector_at(&game->ennemies, 0);
        size_t ennemy_count = vector_size(&game->ennemies);
        for (Square* ennemy=ennemies; ennemy != ennemies + ennemy_count; ennemy++)
        {
            int next_pos_x = ennemy->x + ennemy->direction_x;
            int next_pos_y = ennemy->y + ennemy->direction_y;

            if (game->grid[next_pos_x][next_pos_y] != ENNEMY)
                game_move_square(game, ennemy, ENNEMY);

            if (square_overlap(ennemy, &game->player))
                game->player.alive = 0;
        }
    }
}

void game_draw(GameWindow* game_window, Game* game)
{
    // Draw first ennemis
    for (size_t i=0; i<vector_size(&game->ennemies); i++)
        square_draw(vector_at(&game->ennemies, i), game_window); 

    // Draw player
    square_draw(&game->player, game_window);
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

void game_move_square(Game* game, Square* square, SquareType type)
{
    game->grid[square->x][square->y] = NOTHING;

    square->x += square->direction_x;
    square->y += square->direction_y;

    game->grid[square->x][square->y] = type;
}