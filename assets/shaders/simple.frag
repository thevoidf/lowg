#version 330 core
layout (location = 0) out vec4 color;

in vec3 out_position;
in vec2 out_uv;
in vec4 out_color;

uniform sampler2D tex;

void main()
{
	// color = vec4(out_color.r, out_color.r, out_color.b, texture(tex, out_uv).r);
	color = texture(tex, out_uv);
}
