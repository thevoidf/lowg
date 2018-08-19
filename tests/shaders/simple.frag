#version 330 core

out vec4 color;

in vec2 out_uv;

uniform sampler2D tex;

void main()
{
	// color = vec4(1.0, 1.0, 0.0, 1.0);
	color = texture(tex, out_uv);
}
