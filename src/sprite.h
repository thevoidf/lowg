#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "texture.h"

namespace lowg {

	class Renderer2D;
	
	struct VertexData {
		glm::vec3 vertex;
		glm::vec2 uv;
		float tid;
		glm::vec4 color;
	};
	
	class Sprite
	{
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec2 size;
		glm::vec4 color;
		float angle;
	private:
		std::vector<glm::vec2> uvs;
		Texture* texture;
	public:
		Sprite();
		Sprite(float x, float y, float width, float height, const glm::vec4& color);
		Sprite(float x, float y, float width, float height, Texture* texture);
		Sprite(glm::vec3 position, glm::vec2 size, glm::vec4 color);
		~Sprite();

		virtual void submit(Renderer2D* renderer) const;
	private:
		void init();
	public:
		inline const glm::vec2& getSize() const { return size; }
		inline const glm::vec4& getColor() const { return color; }
		inline const std::vector<glm::vec2>& getUV() const { return uvs; }
		inline const unsigned int getTID() const { return texture ? texture->getID() : 0; }
	};
}
