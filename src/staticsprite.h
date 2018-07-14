#pragma once

#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "shader.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "renderable2d.h"
#include "texture.h"

namespace lowg {
	class StaticSprite : public Renderable2D
	{
	private:
		VertexArray* vertexArray;
		IndexBuffer* indexBuffer;
		Shader& shader;
		Texture* texture;
	public:
		StaticSprite(float x, float y, float width, float height, glm::vec4 color, Shader& shader);
		StaticSprite(float x, float y, float width, float height, const char* texturePath, Shader& shader);
		virtual ~StaticSprite();

		inline const VertexArray* getVAO() const { return vertexArray; }
		inline const IndexBuffer* getIBO() const { return indexBuffer; }
		inline const Texture* getTexture() const { return texture; }
		inline Shader& getShader() const { return shader; }
	};
}
