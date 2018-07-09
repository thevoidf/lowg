#pragma once

#include "renderable2d.h"
#include <glad/glad.h>

namespace lowg {

	class Sprite : public Renderable2D
	{
	public:
		Sprite(float x, float y, float width, float height, const glm::vec4& color);
	};
}
