#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

out vec3 out_position;
out vec2 out_uv;

uniform mat4 pr;
uniform mat4 view = mat4(1.0);
uniform mat4 model = mat4(1.0);

void main()
{
	gl_Position = pr * view * model * vec4(pos, 1.0);
	out_position = pos;
	out_uv = uv;
}
