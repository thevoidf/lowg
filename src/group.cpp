#include "group.h"
#include "renderer2d.h"

namespace lowg {
	Group::Group(const glm::mat4& transform)
		: transformationMatrix(transform)
	{
	}

	void Group::add(Sprite* sprite)
	{
		sprites.push_back(sprite);
	}

	void Group::submit(Renderer2D* renderer) const
	{
		renderer->push(transformationMatrix);
		for (const Sprite* sprite : sprites) {
			sprite->submit(renderer);
		}
		renderer->pop();
	}

}
