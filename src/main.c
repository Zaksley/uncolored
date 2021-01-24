#include "game.h"

int main(int argc, char const *argv[])
{
    GameWindow window;
    if (!game_window_init(&window, 640, 480, "Furry Adventure"))
        return 1;

    Game game;
    game_init(&window, &game);

    /* Loop until the user closes the window */
    while (game_window_is_opened(&window))
    {
        game_window_clear(&window);

        game_update(&window, &game);
        game_draw(&window, &game);

        game_window_update(&window);
    }

    game_window_free(&window);

    return 0;
}
