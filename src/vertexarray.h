#pragma once

#include <vector>
#include "vertexbuffer.h"

namespace lowg {
	class VertexArray
	{
	private:
		unsigned int array;
		std::vector<VertexBuffer*> buffers;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(VertexBuffer* buffer, unsigned int index);
		void bind() const;
		void unbind() const;
	};
}
