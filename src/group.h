#pragma once

#include <vector>
#include "renderable2d.h"

namespace lowg {

	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> renderables;
		glm::mat4 transformationMatrix;
	public:
		Group(const glm::mat4& transform);
		void add(Renderable2D* renderable);
		void submit(Renderer2D* renderer) const override;
	};

}
