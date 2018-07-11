#include "tilelayer.h"

namespace lowg {

	TileLayer::TileLayer(Shader* shader)
		: Layer(new BatchRenderer2D(), shader, glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
	{
	}

	TileLayer::~TileLayer()
	{
	}

}
