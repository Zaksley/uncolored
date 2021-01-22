#version 330 core

layout (location = 0) in vec3 vertexPosition;

uniform vec3 position;
uniform vec3 size;

void main()
{
    gl_Position = vec4(vec3(size.x * vertexPosition.x, size.y * vertexPosition.y, vertexPosition.z) + position, 1.0);
}