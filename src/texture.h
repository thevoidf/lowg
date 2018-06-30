#pragma once

#include <glad/glad.h>
#include <SOIL/SOIL.h>

namespace lowg {
	class Texture
	{
	private:
		unsigned int textureId;
		const char* filePath;
		unsigned char* imageBuffer;
		int width, height;
	public:
		Texture(const char* path);
		~Texture();

		void bind() const;
		void unbind() const;

		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }
	};
}
