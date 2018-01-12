#ifndef UTILS_H
#define UTILS_H

char* file_read(char *path, unsigned int num_chars);

void create_shader(int *shader, const int type, char* source_path, unsigned int source_length);

void create_program(int *shader_program, int vertex_shader, int fragment_shader);

#endif
