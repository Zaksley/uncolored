#version 330 core

layout (location = 0) in vec3 vertexPosition;

uniform float time;
uniform vec3 position;
uniform vec3 size;
uniform bool shake;
uniform float shake_force;

out vec2 vertPos;

void main()
{
    vertPos = vertexPosition.xy;

    gl_Position = vec4(vec3(size.x * vertexPosition.x, size.y * vertexPosition.y, vertexPosition.z) + position, 1.0);
    
    if (shake)
        gl_Position += shake_force * vec4(0.005 * sin(time * 20), 0.02 * sin(time * 30), 0.0, 0.0);
}