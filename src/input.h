#pragma once

#include "GLFW/glfw3.h"

typedef struct
{
    int last_state;
    int current_state;
} KeyState;

typedef struct
{
    GLFWwindow* window;
    KeyState key_states[GLFW_KEY_LAST+1];
} InputState;

void input_state_set_window(InputState* input, GLFWwindow* window);
void input_state_update(InputState* input);

int is_key_released(InputState* input, int key);