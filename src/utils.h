#ifndef UTILS_H
#define UTILS_H

char* file_read(const char *path);
void parse_obj(const char* path, float** vb, float** tex, int *stride, size_t *num_triangles);
GLuint gen_buffer(float* data, size_t size);

#endif
