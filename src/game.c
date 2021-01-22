#include "game.h"

Color color_red = {1.0, 0.0, 0.0, 1.0}; 
Color color_white = {1.0, 1.0, 1.0, 1.0};
Color color_blue = {0.0, 0.0, 1.0, 1.0};
Color color_green = {0.0, 1.0, 0.0, 1.0}; 

void draw(GameWindow* window)
{
    game_window_draw_rectangle(window, 20, 240, 20, 20, color_red);
    game_window_draw_rectangle(window, 200, 20, 20, 20, color_white);
}