#include "shader.h"
#include <GLFW/glfw3.h>

static const float square_vertices[] =
{
    // Triangle 1
    -0.5f,  0.5f, 0.f, // top left
        0.5f,  0.5f, 0.f, // top right
    -0.5f, -0.5f, 0.f, // bottom left

    // Triangle 2
    -0.5f, -0.5f, 0.f, // bottom left
        0.5f,  0.5f, 0.f, // top right
        0.5f, -0.5f, 0.f  // bottom right 
};

int main(int argc, char const *argv[])
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Furry Adventure", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // WARNING
    // C'est la partie sombre ou on charge le carré dans la mémoire de la carte graphique
    glewExperimental = 1;
    GLuint err = glewInit();
    if (err != GLEW_OK)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        glfwTerminate();
        return -1;
    }


    GLuint square_vao;
    glGenVertexArrays(1, &square_vao);
    glBindVertexArray(square_vao);

    GLuint square_vbo;
    glGenBuffers(1, &square_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, square_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, square_vbo);
    glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );

    // C'est fini le truc est chargé en mémoire et la CG sait comment dessiner le carré
    // Maintenant faut charger le shader i.e. le programme que la carte graphique va exécuter pour de vrai

    GLuint shader = load_shaders("shaders/shader.vert", "shaders/shader.frag");
    if (shader == 0)
    {
        glfwTerminate();
        return -1;
    }

    glUseProgram(shader);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 6 vertices total -> 2 triangles
        //glDisableVertexAttribArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
