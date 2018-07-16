#version 330 core
layout (location = 0) out vec4 color;

in vec3 out_position;
in vec2 out_uv;
in float out_tid;
in vec4 out_color;

uniform sampler2D textures[32];
uniform vec2 light_pos;

void main()
{
	float intensity = 1.0 / length(out_position.xy - light_pos);

	vec4 texColor = out_color;
	if (out_tid > 0.0) {
		int tid = int(out_tid - 0.5);
		if (tid == 0)
			texColor = texture(textures[0], out_uv);
		if (tid == 1)
			texColor = texture(textures[1], out_uv);
		if (tid == 2)
			texColor = texture(textures[2], out_uv);
	}
	color = texColor * intensity;
}
