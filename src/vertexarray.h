#pragma once

#include <vector>
#include "buffer.h"

namespace lowg {
	class VertexArray
	{
	private:
		unsigned int array;
		std::vector<Buffer*> buffers;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer* buffer, unsigned int index);
		void bind() const;
		void unbind() const;
	};
}
