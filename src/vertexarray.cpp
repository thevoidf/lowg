#include "vertexarray.h"
#include <glad/glad.h>

namespace lowg {
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &array);
	}

	void VertexArray::addBuffer(VertexBuffer* buffer, unsigned int index)
	{
		bind();
		buffer->bind();

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

		buffer->unbind();
		unbind();
	}
	
	void VertexArray::attribPointer(VertexBuffer *buffer, unsigned int index, unsigned int size, unsigned int type, unsigned int stride, unsigned int offset)
	{
		bind();
		buffer->bind();

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, GL_FALSE, stride, (const GLvoid*) offset);

		buffer->unbind();
		unbind();
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(array);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	VertexArray::~VertexArray() {
		for (unsigned int i = 0; i < buffers.size(); i++) {
			delete buffers[i];
		}
	}
}
