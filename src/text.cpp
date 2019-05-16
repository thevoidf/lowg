#include "text.h"
#include "renderer2d.h"

namespace lowg {
	Text::Text(std::string text, float x, float y, glm::vec4 color, Font* font)
		: Sprite(glm::vec3(x, y, 0.0f), glm::vec2(1.0f, 1.0f), color),
			text(text), font(font)
	{
		ftgl::texture_font_load_glyphs(font->font, text.c_str());
		glGenTextures(1, &font->atlas->id );
		glBindTexture(GL_TEXTURE_2D, font->atlas->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, font->atlas->width, font->atlas->height,
								 0, GL_RED, GL_UNSIGNED_BYTE, font->atlas->data);
	}

	void Text::submit(Renderer2D* renderer) const
	{
		renderer->drawString(text, position, color, font);
	}
}
