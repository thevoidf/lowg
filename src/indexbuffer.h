#pragma once

namespace lowg {
	class IndexBuffer
	{
	private:
		unsigned int buffer;
		unsigned int count;
	public:
		IndexBuffer(unsigned short* data, unsigned int count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		unsigned int getCount() const { return count; }
	};
}
