#pragma once

namespace lowg {
	class VertexBuffer
	{
	private:
		unsigned int buffer;
		unsigned int componentCount;
	public:
		VertexBuffer(const void* data, unsigned int size, unsigned int componentCount);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		const unsigned int getId() const { return buffer; }
		unsigned int getComponentCount() { return componentCount; }
	};
}
