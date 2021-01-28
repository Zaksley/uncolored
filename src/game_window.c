#include "game_window.h"

#include "shader.h"
#include <GLFW/glfw3.h>

const float square_vertices[] =
{
    // Triangle 1
    -0.5f,  0.5f, 0.f, // top left
     0.0f,  0.5f, 0.f, // top right
    -0.5f,  0.0f, 0.f, // bottom left

    // Triangle 2
     0.0f,  0.5f, 0.f, // bottom left
    -0.5f,  0.0f, 0.f, // top right
     0.0f,  0.0f, 0.f,  // bottom right 

    // Triangle 1
     0.0f,  0.5f, 0.f, // top left
     0.5f,  0.5f, 0.f, // top right
     0.0f,  0.0f, 0.f, // bottom left

    // Triangle 2
     0.5f,  0.5f, 0.f, // bottom left
     0.0f,  0.0f, 0.f, // top right
     0.5f,  0.0f, 0.f,  // bottom right 

    // Triangle 1
    -0.5f,  0.0f, 0.f, // top left
     0.0f,  0.0f, 0.f, // top right
    -0.5f, -0.5f, 0.f, // bottom left

    // Triangle 2
     0.0f,  0.0f, 0.f, // bottom left
    -0.5f, -0.5f, 0.f, // top right
     0.0f, -0.5f, 0.f,  // bottom right 

    // Triangle 1
     0.0f,  0.0f, 0.f, // top left
     0.5f,  0.0f, 0.f, // top right
     0.0f, -0.5f, 0.f, // bottom left

    // Triangle 2
     0.5f,  0.0f, 0.f, // bottom left
     0.0f, -0.5f, 0.f, // top right
     0.5f, -0.5f, 0.f,  // bottom right 
};

void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int game_window_init(GameWindow* window, int width, int height, const char* title)
{
    /* Initialize the library */
    if (!glfwInit())
        return 0;

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL

    /* Create a windowed mode window and its OpenGL context */
    window->width = width;
    window->height = height;
    window->glfw_window = glfwCreateWindow(width, height, "Furry Adventure", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 0;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window->glfw_window);
    glfwSetWindowSizeCallback(window->glfw_window, &window_size_callback);

    // WARNING
    // C'est la partie sombre ou on charge le carré dans la mémoire de la carte graphique
    glewExperimental = 1;
    GLuint err = glewInit();
    if (err != GLEW_OK)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        glfwTerminate();
        return 0;
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

    GLuint shader_id = load_shaders("shaders/shader.vert", "shaders/shader.frag");
    if (shader_id == 0)
    {
        glfwTerminate();
        return 0;
    }

    window->shader_id = shader_id;
    glUseProgram(shader_id);

    return 1;
}

int game_window_is_opened(GameWindow* window)
{
    return !glfwWindowShouldClose(window->glfw_window);
}

void game_window_clear(GameWindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void game_window_update(GameWindow* window)
{
    /* Swap front and back buffers */
    glfwSwapBuffers(window->glfw_window);
    /* Poll for and process events */
    glfwPollEvents();
}

void game_window_free(GameWindow* window)
{
    glfwTerminate();
}

void game_window_draw_rectangle(GameWindow* window, float x, float y, float width, float height, Color color)
{
    float gl_pos[3] =
    {
        -1.f + x * 2.f/window->width,
        1.f - y * 2.f/window->height,
         0.f
    };

    float gl_size[3] = 
    {
        2 * (width/window->width),
        2 * (height/window->height),
        1.f
    };

    glProgramUniform1f(window->shader_id, glGetUniformLocation(window->shader_id, "time"), (float)clock());
    glProgramUniform3f(window->shader_id, glGetUniformLocation(window->shader_id, "position"), gl_pos[0], gl_pos[1], gl_pos[2]);
    glProgramUniform3f(window->shader_id, glGetUniformLocation(window->shader_id, "size"), gl_size[0], gl_size[1], gl_size[2]);
    glProgramUniform4f(window->shader_id, glGetUniformLocation(window->shader_id, "color"), color.r, color.g, color.b, color.a);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(square_vertices)/sizeof(square_vertices[0])/3);
}