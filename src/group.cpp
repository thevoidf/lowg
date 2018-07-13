#include "group.h"

namespace lowg {

	Group::Group(const glm::mat4& transform)
		: transformationMatrix(transform)
	{
	}

	void Group::add(Renderable2D* renderable)
	{
		renderables.push_back(renderable);
	}

	void Group::submit(Renderer2D* renderer) const
	{
		renderer->push(transformationMatrix);
		for (const Renderable2D* renderable : renderables) {
			renderable->submit(renderer);
		}
		renderer->pop();
	}

}
