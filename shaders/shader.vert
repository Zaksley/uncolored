#version 330 core

layout (location = 0) in vec3 vertexPosition;

uniform float time;
uniform vec3 position;
uniform vec3 size;

void main()
{
    vec2 wave_amplitude = vec2(0.2);

    vec3 vertex = vertexPosition;
    vertex.x += cos(vertexPosition.y * 2 + 0.2 * time * 10 * 3.8) * wave_amplitude.x
              + sin(vertexPosition.y * 2 + 0.2 * time  / 10 * 6.3) * wave_amplitude.x * 0.3;
    vertex.y += sin(vertexPosition.x * 2 + 0.35 * time / 1500 * 2.4) * wave_amplitude.y
              + cos(vertexPosition.x * 2 + 0.35 * time / 1500 * 5.2) * wave_amplitude.y * 0.3;

    gl_Position = vec4(vec3(size.x * vertexPosition.x, size.y * vertex.y, vertex.z) + position, 1.0);
    gl_Position += vec4(0.005 * sin(time / 100), 0.015 * sin(time / 1000), 0.0, 0.0);
}