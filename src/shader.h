#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

void shader_create(GLuint *shader, const int type, const char* source_path);
void shader_create_program(GLuint *shader_program, GLuint vertex_shader, GLuint fragment_shader);
void shader_create_shader_program(GLuint *shader_id, const char* vert_path, const char* frag_path);
void shader_enable(GLuint shader_id);
void shader_disable(GLuint shader_id);

#endif
