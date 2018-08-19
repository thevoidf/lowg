#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 out_uv;

void main()
{
	gl_Position = vec4(position, 1.0);
	out_uv = uv;
}
