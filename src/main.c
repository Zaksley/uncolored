#include "game.h"

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    GameWindow window;
    if (!game_window_init(&window, 640, 640, "Furry Adventure"))
        return 1;

    Game game;
    game_init(&window, &game);

    /* Loop until the user closes the window */
    while (game_window_is_opened(&window))
    {
        double start_time = glfwGetTime(); 

        game_window_clear(&window);

        game_update(&window, &game);
        game_draw(&window, &game);

        game_window_update(&window);
    
        double end_time = glfwGetTime();
        window.dt = (float)(end_time - start_time);
    }

    game_free(&game);
    game_window_free(&window);

    return 0;
}
