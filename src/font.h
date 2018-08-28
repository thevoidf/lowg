#pragma once

#include "freetype-gl/freetype-gl.h"

class Font
{
private:
	const char* path;
	unsigned int size;
public:
	ftgl::texture_atlas_t* atlas;
	ftgl::texture_font_t* font;
public:
	Font(const char* path, unsigned int size);
	~Font();
};

