#version 330 core

uniform vec3 color;
out vec3 frag_color;

void main()
{
    frag_color = color;
}