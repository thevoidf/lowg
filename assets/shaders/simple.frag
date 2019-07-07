#version 330 core

layout (location = 0) out vec4 color;

in vec3 out_position;
in vec2 out_uv;

uniform sampler2D tex;

void main()
{
	color = texture(tex, out_uv);
}
