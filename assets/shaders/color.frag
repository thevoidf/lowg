#version 330 core

in vec3 out_position;
in vec4 out_color;

out vec4 FragColor;

uniform vec2 light_pos;

void main()
{
	float intensity = 1.0 / length(out_position.xy - light_pos);
  FragColor = out_color * intensity;
}
