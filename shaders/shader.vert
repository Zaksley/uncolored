#version 330 core

layout (location = 0) in vec3 vertexPosition;

uniform vec3 position;
uniform vec3 size;

void main()
{
	mat4 translate = mat4(1.0, 0.0, 0.0, position.x, 
					      0.0, 1.0, 0.0, position.y,  
					      0.0, 0.0, 1.0, position.z,  
					      0.0, 0.0, 0.0, 1.0);

	mat4 scale = mat4(size.x, 0.0, 0.0, 0.0, 
				      0.0, size.y, 0.0, 0.0, 
				      0.0, 0.0, size.z, 0.0, 
				      0.0, 0.0, 0.0, 1.0);

    gl_Position = scale * translate * vec4(vertexPosition, 1.0);
}