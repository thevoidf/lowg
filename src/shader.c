#include <stdio.h>
#include "shader.h"
#include "utils.h"

void create_shader(GLuint *shader, const int type, const char* source_path)
{
	int success;
	char info_log[512];

	if (type == GL_VERTEX_SHADER) {
		*shader = glCreateShader(GL_VERTEX_SHADER);
	} else if (type == GL_FRAGMENT_SHADER) {
		*shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	const char* shader_source = file_read(source_path);
	glShaderSource(*shader, 1, &shader_source, NULL);
	glCompileShader(*shader);

	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*shader, 512, NULL, info_log);
		printf("%s\n", info_log);
	}
}

void create_program(GLuint *shader_program, GLuint vertex_shader, GLuint fragment_shader)
{
	int success;
	char info_log[512];

	*shader_program = glCreateProgram();
	glAttachShader(*shader_program, vertex_shader);
	glAttachShader(*shader_program, fragment_shader);
	glLinkProgram(*shader_program);

	glGetProgramiv(*shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(*shader_program, 512, NULL, info_log);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void create_shader_porgram(GLuint *shader_id, const char* vert_path, const char* frag_path)
{
  GLuint vertex_shader;
  GLuint fragment_shader;

	create_shader(&vertex_shader, GL_VERTEX_SHADER, vert_path);
	create_shader(&fragment_shader, GL_FRAGMENT_SHADER, frag_path);

	create_program(shader_id, vertex_shader, fragment_shader);
}

void shader_enable(GLuint shader_id)
{
  glUseProgram(shader_id);
}

void shader_disable(GLuint shader_id)
{
  glUseProgram(0);
}

