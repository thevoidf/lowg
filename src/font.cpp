#include "font.h"

namespace lowg {
	Font::Font(const char* path, unsigned int size)
		: path(path), size(size)
	{
		atlas = ftgl::texture_atlas_new(512, 512, 1);
		font = ftgl::texture_font_new_from_file(atlas, size, path);
	}

	Font::~Font()
	{
		delete atlas;
		delete font;
	}
}
