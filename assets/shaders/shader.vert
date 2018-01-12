#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 out_color;

uniform mat4 pr;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = pr * view * model * vec4(pos, 1.0);
	out_color = color;
}
