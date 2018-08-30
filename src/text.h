#pragma once

#include "sprite.h"
#include "font.h"

namespace lowg {
	class Text : public Sprite {
	public:
		std::string text;
		Font* font;
	public:
		Text(std::string text, float x, float y, glm::vec4 color, Font* font);
		void submit(Renderer2D* renderer) const override;
	};
}
