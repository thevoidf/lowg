#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"

namespace lowg {
	class Renderable
	{
	protected:
		glm::vec3 position;
		glm::vec2 size;
		glm::vec4 color;

		VertexArray* vertexArray;
		IndexBuffer* indexBuffer;
		Shader& shader;
	public:
		Renderable(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader& shader)
			: position(position), size(size), color(color), shader(shader)
		{
			float vertices[] = {
				-1.0f, 1.0f, 0.0f,
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				1.0f, 1.0f, 0.0f
			};
			unsigned short indices[] = { 0, 1, 2, 2, 3, 0 };
			float colors[] = {
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			vertexArray = new VertexArray();
			indexBuffer = new IndexBuffer(indices, 6);

			vertexArray->addBuffer(new Buffer(vertices, 3 * 4, 3), 0);
			vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
		}

		virtual ~Renderable()
		{
			delete vertexArray;
			delete indexBuffer;
		}

		inline const VertexArray* getVAO() const { return vertexArray; }
		inline const IndexBuffer* getIBO() const { return indexBuffer; }
		inline Shader& getShader() const { return shader; }

		inline const glm::vec3& getPosition() const { return position; }
		inline const glm::vec2& getSize() const { return size; }
		inline const glm::vec4& getColor() const { return color; }

		inline void setPosition(glm::vec3 newPosition) { position = newPosition;  }
		inline void setSize(glm::vec2 newSize) { size = newSize; }
		inline void setColor(glm::vec4 newColor) { color = newColor; }
	};
}
