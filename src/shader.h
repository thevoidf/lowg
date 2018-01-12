#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

void create_shader(GLuint *shader, const int type, const char* source_path);
void create_program(GLuint *shader_program, GLuint vertex_shader, GLuint fragment_shader);
void create_shader_porgram(GLuint *shader_id, const char* vert_path, const char* frag_path);
void shader_enable(GLuint shader_id);
void shader_disable(GLuint shader_id);

#endif
