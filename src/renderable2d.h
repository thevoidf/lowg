#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace lowg {

	struct VertexData {
		glm::vec3 vertex;
		glm::vec4 color;
	};

	class Renderable2D
	{
	protected:
		glm::vec3 position;
		glm::vec2 size;
		glm::vec4 color;
	public:
		Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)
			: position(position), size(size), color(color) { }
		virtual ~Renderable2D() { }

		inline const glm::vec3& getPosition() const { return position; }
		inline const glm::vec2& getSize() const { return size; }
		inline const glm::vec4& getColor() const { return color; }
	};
}
