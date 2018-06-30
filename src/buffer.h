#pragma once

class Buffer
{
private:
  unsigned int buffer;
  unsigned int componentCount;
public:
  Buffer(float* data, unsigned int count, unsigned int componentCount);
  ~Buffer();

  void bind() const;
  void unbind() const;

  unsigned int getComponentCount() { return componentCount; }
};
