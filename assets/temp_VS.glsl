#version 150 core

in vec3 position;
in vec3 color;
in vec3 normal;
in vec2 texcoord;

out vec3 Pos;
out vec3 Color;
out vec3 Normal;
out vec2 Texcoord;

uniform mat4 transform;

void main()
{
    Color = color;
    Texcoord = texcoord;
	Normal = (transform*vec4(normal, 0.0)).xyz;
	Pos = (transform*vec4(position, 1.0)).xyz;  
	gl_Position = transform*vec4(position, 1.0);
}
