#include "square.h"

void square_draw(Square* square, GameWindow* game_window)
{
    game_window_draw_rectangle(game_window,
                                SIZE_SQUARE / 2 + square->x * SIZE_SQUARE,
                                SIZE_SQUARE / 2 + square->y * SIZE_SQUARE,
                                square->size * SIZE_SQUARE,
                                square->size * SIZE_SQUARE,
                                square->color);
}