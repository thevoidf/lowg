#include <deque>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "renderer2d.h"
#include "shader.h"
#include "renderable2d.h"
#include "staticsprite.h"

namespace lowg {
	class SimpleRenderer : public Renderer2D
	{
		public:
			std::deque<const StaticSprite*> renderQueue;

			void submit(const Renderable2D* renderable) override;
			void flush() override;
	};
}
