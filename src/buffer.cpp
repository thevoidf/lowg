#include "buffer.h"
#include <glad/glad.h>

Buffer::Buffer(float* data, unsigned int count, unsigned int componentCount)
{
  this->componentCount = componentCount;

  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::bind() const
{
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void Buffer::unbind() const
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Buffer::~Buffer()
{
}
