#version 330 core

out vec4 FragColor;
in vec4 out_color;
in vec2 out_tex;

uniform sampler2D tex;

void main()
{
  FragColor = texture(tex, out_tex);
}
