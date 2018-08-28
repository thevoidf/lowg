#pragma once

#include "renderable2d.h"
#include "font.h"

namespace lowg {
	class Text : public Renderable2D {
	public:
		std::string text;
		Font* font;
	public:
		Text(std::string text, float x, float y, glm::vec4 color, Font* font);
		void submit(Renderer2D* renderer) const override;
	};
}
