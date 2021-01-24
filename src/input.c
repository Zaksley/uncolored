#include "input.h"

void input_state_set_window(InputState* input, GLFWwindow* window)
{
    input->window = window;
}

void update_key(InputState* input, int key)
{
    input->key_states[key].last_state = input->key_states[key].current_state;
    input->key_states[key].current_state = glfwGetKey(input->window, key);
}

void input_state_update(InputState* input)
{
    update_key(input, GLFW_KEY_RIGHT);
    update_key(input, GLFW_KEY_LEFT);
    update_key(input, GLFW_KEY_UP);
    update_key(input, GLFW_KEY_DOWN);
}

int is_key_released(InputState* input, int key)
{
    return input->key_states[key].current_state == GLFW_RELEASE && input->key_states[key].last_state == GLFW_PRESS;
}