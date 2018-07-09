#include <deque>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "renderer.h"

namespace lowg {
	class Simple3DRenderer
	{
		public:
			std::deque<const Renderable3D*> renderQueue;

			void submit(const Renderable3D* renderable);
			void flush();
	};
}
