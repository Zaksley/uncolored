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
    game.size_x = 640/game.player.size;
    game.size_y = 480/game.player.size; 

    Square Ennemy; 
    Ennemy.x = 336;
    Ennemy.y = 48; 
    Ennemy.direction_x = 1;
    Ennemy.direction_y = 0; 

    // - Init Board
    for(int i=0; i<game.size_x; i++)
    {
        //fprintf(stderr, "i : %d", i); 
        for(int j=0; j<game.size_y; j++)
        {
            game.board[i][j] = -1; 
        }
    }

    int a = Ennemy.x / 32;
    int b = Ennemy.y / 32; 
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    game.board[a][b] = 1; 
    game.board_square[a][b] = Ennemy; 

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
