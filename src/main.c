#include "game_window.h"

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

        Color color = {1.0, 0.0, 0.0, 1.0};
        game_window_draw_rectangle(&window, 20, 240, 20, 20, color);
        game_window_draw_rectangle(&window, 200, 20, 40, 20, color);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.glfw_window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
