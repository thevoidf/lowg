#pragma once

#include <vector>
#include <glm/mat4x4.hpp>
#include "sprite.h"

namespace lowg {

	class Renderer2D;

	class Group : public Sprite
	{
	private:
		std::vector<Sprite*> sprites;
		glm::mat4 transformationMatrix;
	public:
		Group(const glm::mat4& transform);
		void add(Sprite* sprite);
		void submit(Renderer2D* renderer) const override;
	};
}
