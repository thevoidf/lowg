#version 330 core
layout (location = 0) out vec4 color;

in vec3 out_position;
in vec2 out_uv;
in vec4 out_color;

uniform sampler2D tex;
uniform vec2 light_pos;

void main()
{
	float intensity = 1.0 / length(out_position.xy - light_pos);
  color = texture(tex, out_uv) * out_color * intensity;
}
