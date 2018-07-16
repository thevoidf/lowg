#pragma once

#include <glad/glad.h>
#include "renderable2d.h"
#include "texture.h"

namespace lowg {

	class Sprite : public Renderable2D
	{
	public:
		Sprite(float x, float y, float width, float height, const glm::vec4& color);
		Sprite(float x, float y, float width, float height, Texture* texture);
	};
}
