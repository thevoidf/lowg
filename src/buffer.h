#pragma once

namespace lowg {
	class Buffer
	{
	private:
		unsigned int buffer;
		unsigned int componentCount;
	public:
		Buffer(const void* data, unsigned int count, unsigned int componentCount);
		~Buffer();

		void bind() const;
		void unbind() const;

		unsigned int getComponentCount() { return componentCount; }
	};
}
