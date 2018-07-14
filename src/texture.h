#pragma once

#include <glad/glad.h>
#include "utils.h"

namespace lowg {
	class Texture
	{
	private:
		unsigned int textureId;
		const char* filePath;
		unsigned int width, height;
	public:
		Texture(const char* path);
		~Texture();

		void bind() const;
		void unbind() const;

		inline unsigned int getWidth() const { return width; }
		inline unsigned int getHeight() const { return height; }
	};
}
