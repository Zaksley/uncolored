#include "game.h"

int main(int argc, char const *argv[])
{
    GameWindow window;

    if (!game_window_init(&window, 640, 480, "Furry Adventure"))
        return 1;

    Game game;
    game.player.x = 16;
    game.player.y = 16;
    game.player.size = 32;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.glfw_window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        game_update(&window, &game);
        game_draw(&window, &game);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.glfw_window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    game_window_free(&window);

    return 0;
}
