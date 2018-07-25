#version 330 core
layout (location = 0) out vec4 color;

in vec3 out_position;
in vec2 out_uv;
in float out_tid;
in vec4 out_color;

// uniform sampler2D textures[18];
uniform sampler2D tex;

void main()
{
	/*
	if (out_tid > 0.0) {
		int tid = int(out_tid - 0.5);
		if (tid == 0)
			texColor = texture(textures[0], out_uv);
		if (tid == 1)
			texColor = texture(textures[1], out_uv);
		if (tid == 2)
			texColor = texture(textures[2], out_uv);
		if (tid == 3)
			texColor = texture(textures[3], out_uv);
		if (tid == 4)
			texColor = texture(textures[4], out_uv);
		if (tid == 5)
			texColor = texture(textures[5], out_uv);
		if (tid == 6)
			texColor = texture(textures[6], out_uv);
		if (tid == 7)
			texColor = texture(textures[7], out_uv);
		if (tid == 8)
			texColor = texture(textures[8], out_uv);
		if (tid == 9)
			texColor = texture(textures[9], out_uv);
		if (tid == 10)
			texColor = texture(textures[10], out_uv);
		if (tid == 11)
			texColor = texture(textures[11], out_uv);
		if (tid == 12)
			texColor = texture(textures[12], out_uv);
		if (tid == 13)
			texColor = texture(textures[13], out_uv);
		if (tid == 14)
			texColor = texture(textures[14], out_uv);
		if (tid == 15)
			texColor = texture(textures[15], out_uv);
	} */
	color = texture(tex, out_uv);
}
