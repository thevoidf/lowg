#include <deque>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "renderer.h"
#include "renderable.h"

namespace lowg {
	class SimpleRenderer : public Renderer
	{
		public:
			std::deque<const Renderable*> renderQueue;

			void submit(const Renderable* renderable) override;
			void flush() override;
	};
}
