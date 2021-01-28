#version 330 core

uniform float time;
uniform vec4 color;
out vec4 frag_color;

void main()
{
    frag_color = vec4(sin(time / 1000), sin(time / 500), color.b, 1.0);//color;
}