#include "game.h"
#define SIZE_SQUARE 32

Color color_red = {1.0, 0.0, 0.0, 1.0};
Color color_white = {1.0, 1.0, 1.0, 1.0};
Color color_blue = {0.0, 0.0, 1.0, 1.0};
Color color_green = {0.0, 1.0, 0.0, 1.0};
Color color_violet = {0.75, 0.0, 0.75, 1.0}; 

int is_key_released(KeyState state)
{
    return state.current_state == GLFW_RELEASE && state.last_state == GLFW_PRESS;
}

void game_update(GameWindow* window, Game* game)
{
    game->right_state.last_state = game->right_state.current_state;
    game->right_state.current_state = glfwGetKey(window->glfw_window, GLFW_KEY_RIGHT);

    game->left_state.last_state = game->left_state.current_state;
    game->left_state.current_state = glfwGetKey(window->glfw_window, GLFW_KEY_LEFT);

    game->up_state.last_state = game->up_state.current_state;
    game->up_state.current_state = glfwGetKey(window->glfw_window, GLFW_KEY_UP);

    game->down_state.last_state = game->down_state.current_state;
    game->down_state.current_state = glfwGetKey(window->glfw_window, GLFW_KEY_DOWN);

    if (is_key_released(game->right_state))
    {
        game->board[game->player.x/SIZE_SQUARE][game->player.y/SIZE_SQUARE] = -1; 
        game->player.x += game->player.size;
        
    }
    if (is_key_released(game->left_state))
    {
        game->board[game->player.x/SIZE_SQUARE][game->player.y/SIZE_SQUARE] = -1;
        game->player.x -= game->player.size;
    }
    if (is_key_released(game->up_state))
    {
        game->board[game->player.x/SIZE_SQUARE][game->player.y/SIZE_SQUARE] = -1;
        game->player.y -= game->player.size;
    }
    if (is_key_released(game->down_state))
    {
        game->board[game->player.x/SIZE_SQUARE][game->player.y/SIZE_SQUARE] = -1;
        game->player.y += game->player.size;
    }

    int board_x = game->player.x / SIZE_SQUARE;
    int board_y = game->player.y / SIZE_SQUARE; 
    game->board[board_x][board_y] = 1;

    //TODO Fonction qui check si y'avait pas déjà quelque chose =>>> Mort du player

    // Others squares
    Square* Ennemy;
    for(int i=0; i<game->size_x; i++)
    {
        for(int j=0; j<game->size_y; j++)
        {
            if (game->board[i][j] != -1 )
            {
                Ennemy = &game->board_square[i][j]; 
                Ennemy->x += SIZE_SQUARE * Ennemy->direction_x;
                Ennemy->y += SIZE_SQUARE * Ennemy->direction_y; 
            }
        }
    }

}

void game_draw(GameWindow* window, Game* game)
{


    // Draw player
    game_window_draw_rectangle(window, game->player.x, game->player.y, game->player.size, game->player.size, color_violet);

    //Draw first ennemis

    int pos_x;
    int pos_y;  
    for(int i=0; i<game->size_x; i++)
    {
        for(int j=0; j<game->size_y; j++)
        {
            if (game->board[i][j] != -1)
            {
                pos_x = 16 + i*SIZE_SQUARE;
                pos_y = 16 + j*SIZE_SQUARE; 
                game_window_draw_rectangle(window, pos_x, pos_y, SIZE_SQUARE, SIZE_SQUARE, color_red);
            }
        }
    }
}
