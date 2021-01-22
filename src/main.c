#include "game.h"

int main(int argc, char const *argv[])
{
    GameWindow window;

    if (!game_window_init(&window, 640, 480, "Furry Adventure"))
    {
        return 1;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.glfw_window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw(&window);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.glfw_window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
