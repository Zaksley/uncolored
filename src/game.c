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

void game_init(GameWindow* game_window, Game* game)
{
    input_state_set_window(&game->input, game_window->glfw_window);
    game->player.x = 2;
    game->player.y = 2;
    game->player.size = 1;
    game->size_x = GRID_SIZE;
    game->size_y = GRID_SIZE; 

    Square ennemy; 
    ennemy.x = 10;
    ennemy.y = 10; 
    ennemy.direction_x = 1;
    ennemy.direction_y = 0; 

    // - Init Board
    for(int i=0; i<game->size_x; i++)
    {
        //fprintf(stderr, "i : %d", i); 
        for(int j=0; j<game->size_y; j++)
        {
            game->board[i][j] = -1; 
        }
    }

    int a = ennemy.x;
    int b = ennemy.y; 
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    game->board[a][b] = 1; 
    game->board_square[a][b] = ennemy; 
}

void game_update(GameWindow* game_window, Game* game)
{
    input_state_update(&game->input);

    if (is_key_released(&game->input, GLFW_KEY_RIGHT))
    {
        game->board[game->player.x][game->player.y] = -1; 
        game->player.x += 1;
        
    }
    if (is_key_released(&game->input, GLFW_KEY_LEFT))
    {
        game->board[game->player.x][game->player.y] = -1;
        game->player.x -= 1;
    }
    if (is_key_released(&game->input, GLFW_KEY_UP))
    {
        game->board[game->player.x][game->player.y] = -1;
        game->player.y -= 1;
    }
    if (is_key_released(&game->input, GLFW_KEY_DOWN))
    {
        game->board[game->player.x][game->player.y] = -1;
        game->player.y += 1;
    }

    game->board[game->player.x][game->player.y] = 1;

    //TODO Fonction qui check si y'avait pas déjà quelque chose =>>> Mort du player

    // Others squares
    Square* ennemy;
    for(int i=0; i<game->size_x; i++)
    {
        for(int j=0; j<game->size_y; j++)
        {
            if (game->board[i][j] != -1 )
            {
                ennemy = &game->board_square[i][j]; 
                ennemy->x += SIZE_SQUARE * ennemy->direction_x;
                ennemy->y += SIZE_SQUARE * ennemy->direction_y; 
            }
        }
    }

}

void game_draw(GameWindow* game_window, Game* game)
{
    // Draw player
    square_draw(&game->player, game_window);

    //Draw first ennemis
    int pos_x;
    int pos_y;  
    for (int i=0; i<game->size_x; i++)
    {
        for (int j=0; j<game->size_y; j++)
        {
            if (game->board[i][j] != -1)
            {
                pos_x = SIZE_SQUARE/2 + i*SIZE_SQUARE;
                pos_y = SIZE_SQUARE/2 + j*SIZE_SQUARE; 
                game_window_draw_rectangle(game_window, pos_x, pos_y, SIZE_SQUARE, SIZE_SQUARE, color_red);
            }
        }
    }
}
