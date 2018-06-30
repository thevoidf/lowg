#pragma once

#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
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
		glm::vec2 size;
		glm::vec4 color;

		VertexArray* vertexArray;
		IndexBuffer* indexBuffer;
		Texture* texture;
	public:
		Renderable(Shader& shader, glm::vec3 position, glm::vec2 size)
			: shader(shader), position(position), size(size)
		{
			float vertices[] = {
				-1.0f, 1.0f, 0.0f,
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				1.0f, 1.0f, 0.0f
			};
			unsigned short indices[] = { 0, 1, 2, 2, 3, 0 };

			vertexArray = new VertexArray();
			indexBuffer = new IndexBuffer(indices, 6);

			texture = NULL;

			vertexArray->addBuffer(new Buffer(vertices, 3 * 4, 3), 0);
		}

		Renderable(Shader& shader, glm::vec3 position, glm::vec2 size, glm::vec4 color)
			: Renderable(shader, position, size)
		{
			float colors[] = {
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
		}

		Renderable(Shader& shader, glm::vec3 position, glm::vec2 size, const char* texture_path)
			: Renderable(shader, position, size)
		{
			float texCoords[] = {
				0.0f, 0.0f,
				0.0f, 1.0f,
				1.0f, 1.0f,
				1.0f, 0.0f
			};

			texture = new Texture(texture_path);
			vertexArray->addBuffer(new Buffer(texCoords, 2 * 4, 2), 1);
		}

		virtual ~Renderable()
		{
			delete vertexArray;
			delete indexBuffer;
			delete texture;
		}

		inline const VertexArray* getVAO() const { return vertexArray; }
		inline const IndexBuffer* getIBO() const { return indexBuffer; }
		inline const Texture* getTexture() const { return texture; }
		inline Shader& getShader() const { return shader; }

		inline const glm::vec3& getPosition() const { return position; }
		inline const glm::vec2& getSize() const { return size; }
		inline const glm::vec4& getColor() const { return color; }

		inline void setPosition(glm::vec3 newPosition) { position = newPosition;  }
		inline void setSize(glm::vec2 newSize) { size = newSize; }
		inline void setColor(glm::vec4 newColor) { color = newColor; }
	};
}
