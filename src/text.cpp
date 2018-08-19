#include "text.h"

namespace lowg {
	Text::Text(std::string text, float x, float y, glm::vec4 color)
		: Renderable2D(glm::vec3(x, y, 0.0f), glm::vec2(1.0f, 1.0f), color),
			text(text)
	{
	}

	void Text::submit(Renderer2D* renderer) const
	{
		renderer->drawString(text, position, color);
	}
}
