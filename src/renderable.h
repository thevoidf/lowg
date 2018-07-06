#pragma once

#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "indexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "shader.h"

namespace lowg {
	class Renderable
	{
	protected:
		Shader& shader;
		glm::vec3 position;
		VertexArray* vertexArray;

	public:
		Renderable(Shader& shader, glm::vec3 position);
		virtual ~Renderable();

		inline const VertexArray* getVAO() const { return vertexArray; }
		inline Shader& getShader() const { return shader; }

		inline const glm::vec3& getPosition() const { return position; }
		inline void setPosition(glm::vec3 newPosition) { position = newPosition;  }
	};
}
