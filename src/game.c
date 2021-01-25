#include "game.h"

Color color_red = {1.0, 0.0, 0.0, 1.0};
Color color_white = {1.0, 1.0, 1.0, 1.0};
Color color_blue = {0.0, 0.0, 1.0, 1.0};
Color color_green = {0.0, 1.0, 0.0, 1.0};
Color color_violet = {0.75, 0.0, 0.75, 1.0}; 

void square_draw(Square* square, GameWindow* game_window)
{
    game_window_draw_rectangle(game_window,
                                SIZE_SQUARE / 2 + square->x * SIZE_SQUARE,
                                SIZE_SQUARE / 2 + square->y * SIZE_SQUARE,
                                square->size * SIZE_SQUARE,
                                square->size * SIZE_SQUARE,
                                square->color);
}

Square empty_square(int x, int y)
{
    Square ennemy = {.color = color_green, .x = x, .y = y, .direction_x = 0, .direction_y = 0, .size = 1};
    return ennemy; 
}

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
        {
            game->board[i][j] = -1; 
            //game->board_square[i][j] = empty_square(i,j); 
        }
    }


    Square ennemy; 
    ennemy.x = 2;
    ennemy.y = 2; 
    ennemy.size = 1;
    ennemy.color = color_red; 
    ennemy.direction_x = 1;
    ennemy.direction_y = 0; 

    game->board[ennemy.x][ennemy.y] = 1; 
    game->board_square[ennemy.x][ennemy.y] = ennemy; 
}

void game_update(GameWindow* game_window, Game* game)
{
    input_state_update(&game->input);
    int moved = 0; 

    if (is_key_released(&game->input, GLFW_KEY_RIGHT))
    {
        game->board[game->player.x][game->player.y] = -1; 
        game->player.x += 1;
        moved = 1; 
    }
    if (is_key_released(&game->input, GLFW_KEY_LEFT))
    {
        game->board[game->player.x][game->player.y] = -1;
        game->player.x -= 1;
        moved = 1; 
    }
    if (is_key_released(&game->input, GLFW_KEY_UP))
    {
        game->board[game->player.x][game->player.y] = -1;
        game->player.y -= 1;
        moved = 1; 
    }
    if (is_key_released(&game->input, GLFW_KEY_DOWN))
    {
        game->board[game->player.x][game->player.y] = -1;
        game->player.y += 1;
        moved = 1; 
    }

    game->board[game->player.x][game->player.y] = 1;

    //TODO Fonction qui check si y'avait pas déjà quelque chose =>>> Mort du player


    if (moved)
    {
        // Others squares
        Square* ennemy;
        for(int i=0; i<game->size_x; i++)
        {
            for(int j=0; j<game->size_y; j++)
            {
                if (game->board[i][j] != -1 )
                {
                    ennemy = &game->board_square[i][j]; 
                    
                    ennemy->x += ennemy->direction_x;
                    ennemy->y += ennemy->direction_y; 

                    //game->board[i][j] = -1; 
                    //game->board[ennemy->x][ennemy->y] = 1;

                    //game->board_square[i][j] = *ennemy;
 
                }
            }
        }
    }
}

void game_draw(GameWindow* game_window, Game* game)
{
    // Draw player
    square_draw(&game->player, game_window);

    //Draw first ennemis
    for (int i=0; i<game->size_x; i++)
    {
        for (int j=0; j<game->size_y; j++)
        {
            if (game->board[i][j] != -1)
            {
                square_draw(&game->board_square[i][j], game_window); 
            }
        }
    }
}
