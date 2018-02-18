#include <stdlib.h>
#include <glad/glad.h>
#include "renderer.h"

void render(GLuint position_buffer, GLuint color_buffer,
						GLuint* indices,
						GLint size1, GLsizei stride1,
						GLint size2, GLsizei stride2,
						GLsizei draw_count,
						GLenum mode)
{
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, size1, GL_FLOAT, GL_FALSE, stride1, 0);

	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, size2, GL_FLOAT, GL_FALSE, stride2, 0);

	if (mode == GL_TRIANGLES) {
		glDrawArrays(GL_TRIANGLES, 0, draw_count);
	} else {
		glDrawElements(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, indices);
	}
}
