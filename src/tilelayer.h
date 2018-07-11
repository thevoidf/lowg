#pragma once

#include "layer.h"
#include "batchrenderer2d.h"

namespace lowg {
	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader* shader);
		~TileLayer();
	};
}
