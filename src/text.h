#pragma once

#include "renderable2d.h"

namespace lowg {
	class Text : public Renderable2D {
	private:
		std::string text;
	public:
		Text(std::string text, float x, float y, glm::vec4 color);
		void submit(Renderer2D* renderer) const override;
	};
}
