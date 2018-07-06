#include <deque>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "renderer.h"
#include "renderable.h"

namespace lowg {
	class Simple3DRenderer : public Renderer
	{
		public:
			std::deque<const Renderable3D*> renderQueue;

			void submit(const Renderable* renderable) override;
			void flush() override;
	};
}
