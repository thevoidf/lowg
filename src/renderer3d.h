#include <deque>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>

namespace lowg {
	class Renderer3D {
	public:
		std::deque<const Renderable3D*> renderQueue;

		void submit(const Renderable3D* renderable);
		void flush();
	};
}
