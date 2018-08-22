#pragma once

#include <glad/glad.h>
#include "utils.h"

namespace lowg {
	class Texture
	{
	private:
		unsigned int textureId;
		const char* path;
		unsigned int width, height;
	public:
		int internalFormat;
		int format;
	public:
		Texture(const char* path);
		Texture(const char* path, int format);
		Texture(const char* path, int internalFormat, int format);
		~Texture();

		void bind() const;
		void unbind() const;

		inline const unsigned int getID() const { return textureId; }
		inline unsigned int getWidth() const { return width; }
		inline unsigned int getHeight() const { return height; }
	};
}
