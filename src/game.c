#include "game.h"

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
        game->player.x += game->player.size;
    }
    if (is_key_released(game->left_state))
    {
        game->player.x -= game->player.size;
    }
    if (is_key_released(game->up_state))
    {
        game->player.y -= game->player.size;
    }
    if (is_key_released(game->down_state))
    {
        game->player.y += game->player.size;
    }
}

void game_draw(GameWindow* window, Game* game)
{
    // Draw player
    game_window_draw_rectangle(window, game->player.x, game->player.y, game->player.size, game->player.size, color_violet);
}