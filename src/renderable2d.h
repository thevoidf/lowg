#pragma once

#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "renderable.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "shader.h"

namespace lowg {
	class Renderable2D : public Renderable
	{
	protected:
		glm::vec2 size;
		glm::vec4 color;

		IndexBuffer* indexBuffer;
		Texture* texture;
	public:
		Renderable2D(Shader& shader, glm::vec3 position, glm::vec2 size);
		Renderable2D(Shader& shader, glm::vec3 position, glm::vec2 size, glm::vec4 color);
		Renderable2D(Shader& shader, glm::vec3 position, glm::vec2 size, const char* texture_path);
		virtual ~Renderable2D();

		inline const IndexBuffer* getIBO() const { return indexBuffer; }
		inline const Texture* getTexture() const { return texture; }
		inline const glm::vec2& getSize() const { return size; }
		inline const glm::vec4& getColor() const { return color; }

		inline void setSize(glm::vec2 newSize) { size = newSize; }
		inline void setColor(glm::vec4 newColor) { color = newColor; }
	};
}
