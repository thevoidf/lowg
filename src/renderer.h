#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>

void render(GLuint position_buffer, GLuint color_buffer,
						GLuint* indices,
						GLint size1, GLsizei stride1,
						GLint size2, GLsizei stride2,
						GLsizei draw_count,
						GLenum mode);

#endif
