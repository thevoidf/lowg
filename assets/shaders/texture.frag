#version 330 core

in vec2 out_tex_coord;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
  FragColor = texture(tex, out_tex_coord);
}
