#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>
#include "utils.h"

char* file_read(char *path, unsigned int num_chars)
{
	FILE* f;
	char* con = malloc(sizeof(char) + num_chars);
	size_t n = 0;
	int c;

	f = fopen(path, "r");
	if (f == NULL) {
		printf("Cant open file: %s", path);
		return NULL;
	}

	while ((c = fgetc(f)) != EOF) {
		con[n++] = (char) c;
	}

	con[n] = '\0';

	return con;
}

void create_shader(int *shader, const int type, char* source_path, unsigned int source_length)
{
	int length = source_length;
	int success;
	char info_log[512];

	if (length == 0) {
		length = 1000;
	}

	if (type == GL_VERTEX_SHADER) {
		*shader = glCreateShader(GL_VERTEX_SHADER);
	} else if (type == GL_FRAGMENT_SHADER) {
		*shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	const char* shader_source = file_read(source_path, length);
	glShaderSource(*shader, 1, &shader_source, NULL);
	glCompileShader(*shader);

	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*shader, 512, NULL, info_log);
		printf("%s\n", info_log);
	}
}

void create_program(int *shader_program, int vertex_shader, int fragment_shader)
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
