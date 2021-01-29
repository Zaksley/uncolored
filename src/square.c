#include "square.h"

Square square_create(int x, int y, int size, Color color, int direction_x, int direction_y)
{
    Square square = { x, y, size, color, direction_x, direction_y, 1, 0, 0, x, y };
    return square;
}

int square_overlap(Square* s1, Square* s2)
{
    return s1->x == s2->x && s1->y == s2->y;
}

void square_draw(Square* square, GameWindow* game_window, Effect effect)
{
    float x, y;
    if (square->moving)
    {
        x = square->move_x;
        y = square->move_y;
    }
    else
    {
        x = square->x;
        y = square->y;
    }

    game_window_draw_rectangle(game_window,
                                SIZE_SQUARE / 2 + x * SIZE_SQUARE,
                                SIZE_SQUARE / 2 + y * SIZE_SQUARE,
                                square->size * SIZE_SQUARE,
                                square->size * SIZE_SQUARE,
                                square->color,
                                effect);
}