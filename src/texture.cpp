#include "texture.h"

namespace lowg {
	Texture::Texture(const char* path)
		:	Texture(path, GL_RGB, GL_BGR)
	{
	}

	Texture::Texture(const char* path, int format)
		:	Texture(path, format, format)
	{
	}

	Texture::Texture(const char* path, int internalFormat, int format)
		: path(path), internalFormat(internalFormat), format(format)
	{
		BYTE* pixels = load_image(path, width, height);
		
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &textureId);
	}

}
