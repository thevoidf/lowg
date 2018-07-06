#include "renderable.h"

namespace lowg {
	Renderable::Renderable(Shader& shader, glm::vec3 position)
		: shader(shader), position(position)
	{
		vertexArray = new VertexArray();
	}

	Renderable::~Renderable()
	{
		delete vertexArray;
	}
}
