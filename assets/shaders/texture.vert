#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex_coord;

out vec2 out_tex_coord;

uniform mat4 pr;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = pr * view * model * vec4(pos, 1.0);
	out_tex_coord = tex_coord;
}
