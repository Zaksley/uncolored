#pragma once

#include "shader.h"
#include <GLFW/glfw3.h>
#include <time.h>

typedef struct
{
    float r, g, b, a; 
} Color;

typedef struct
{
    int width, height;
    GLuint shader_id;
    GLFWwindow* glfw_window;
    
} GameWindow;

typedef struct
{
    int shake;
    int fade;
    float dir_x, dir_y;
} Effect;

int game_window_init(GameWindow* window, int width, int height, const char* title);
int game_window_is_opened(GameWindow* window);
void game_window_clear(GameWindow* window);
void game_window_update(GameWindow* window);
void game_window_free(GameWindow* window);
void game_window_draw_rectangle(GameWindow* window, float x, float y, float width, float height, Color color, Effect effect);

Effect no_effect();