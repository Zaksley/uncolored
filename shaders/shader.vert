#version 330 core

layout (location = 0) in vec3 vertexPosition;

uniform float time;
uniform vec3 position;
uniform vec3 size;

void main()
{
    gl_Position = vec4(vec3(size.x * vertexPosition.x, size.y * vertexPosition.y, vertexPosition.z) + position, 1.0);
    gl_Position += vec4(0.005 * sin(time / 100), 0.015 * sin(time / 1000), 0.0, 0.0);
}