#include "square.h"

Square square_create(int x, int y, int size, Color color, int direction_x, int direction_y)
{
    Square square = { x, y, size, color, direction_x, direction_y };
    return square;
}

void square_draw(Square* square, GameWindow* game_window)
{
    game_window_draw_rectangle(game_window,
                                SIZE_SQUARE / 2 + square->x * SIZE_SQUARE,
                                SIZE_SQUARE / 2 + square->y * SIZE_SQUARE,
                                square->size * SIZE_SQUARE,
                                square->size * SIZE_SQUARE,
                                square->color);
}