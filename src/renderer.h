#pragma once

#include "renderable2d.h"

namespace lowg {
	class Renderer
	{
		public:
			virtual void submit(const Renderable* renderable) = 0;
			virtual void flush() = 0;
	};
}
