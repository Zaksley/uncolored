#include "game.h"

Color color_red = {1.0, 0.0, 0.0, 1.0};
Color color_white = {1.0, 1.0, 1.0, 1.0};
Color color_blue = {0.0, 0.0, 1.0, 1.0};
Color color_green = {0.0, 1.0, 0.0, 1.0};
Color color_violet = {0.75, 0.0, 0.75, 1.0}; 

void game_init(GameWindow* game_window, Game* game)
{
    input_state_set_window(&game->input, game_window->glfw_window);
 
    game->player.x = 0;
    game->player.y = 0;
    game->player.size = 1;
    game->player.color = color_white; 
    game->size_x = GRID_SIZE;
    game->size_y = GRID_SIZE;

    // - Init Board
    for(int i=0; i<game->size_x; i++)
    {
        for(int j=0; j<game->size_y; j++)
            game->grid[i][j] = NOTHING; 
    }

    vector_init(&game->ennemies, 10);

    Square ennemy; 
    ennemy.x = 2;
    ennemy.y = 2; 
    ennemy.size = 1;
    ennemy.color = color_red; 
    ennemy.direction_x = 1;
    ennemy.direction_y = 0;

    vector_push(&game->ennemies, ennemy);

    game->grid[ennemy.x][ennemy.y] = ENNEMY; 
}

void game_update(GameWindow* game_window, Game* game)
{
    input_state_update(&game->input);

    int moved = 0; 

    if (is_key_released(&game->input, GLFW_KEY_RIGHT))
    {
        game->grid[game->player.x][game->player.y] = -1; 
        game->player.x += 1;
        moved = 1; 
    }
    if (is_key_released(&game->input, GLFW_KEY_LEFT))
    {
        game->grid[game->player.x][game->player.y] = -1;
        game->player.x -= 1;
        moved = 1; 
    }
    if (is_key_released(&game->input, GLFW_KEY_UP))
    {
        game->grid[game->player.x][game->player.y] = -1;
        game->player.y -= 1;
        moved = 1; 
    }
    if (is_key_released(&game->input, GLFW_KEY_DOWN))
    {
        game->grid[game->player.x][game->player.y] = -1;
        game->player.y += 1;
        moved = 1; 
    }

    game->grid[game->player.x][game->player.y] = 1;

    //TODO Fonction qui check si y'avait pas déjà quelque chose =>>> Mort du player

    if (moved)
    {
        // Others squares
        Square* ennemies = vector_at(&game->ennemies, 0);
        for (Square* ennemy=ennemies; ennemy != ennemies + vector_size(&game->ennemies); ennemy++)
        {
            game->grid[ennemy->x][ennemy->y] = NOTHING;

            ennemy->x += ennemy->direction_x;
            ennemy->y += ennemy->direction_y; 

            game->grid[ennemy->x][ennemy->y] = ENNEMY;
        }
    }
}

void game_draw(GameWindow* game_window, Game* game)
{
    // Draw player
    square_draw(&game->player, game_window);

    // Draw first ennemis
    for (size_t i=0; i<vector_size(&game->ennemies); i++)
        square_draw(vector_at(&game->ennemies, i), game_window); 
}

void game_free(Game* game)
{
    vector_free(&game->ennemies);
}