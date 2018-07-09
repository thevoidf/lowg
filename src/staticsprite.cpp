#include "staticsprite.h"

namespace lowg {
	StaticSprite::StaticSprite(float x, float y, float width, float height, glm::vec4 color, Shader& shader)
		: Renderable2D(glm::vec3(x, y, 0.0f), glm::vec2(width, height), color), shader(shader)
	{
		vertexArray = new VertexArray();
		float vertices[] = {
			0.0f, 0.0f, 0.0f,
			0.0f, height, 0.0f,
			width, height, 0.0f,
			width, 0.0f, 0.0f
		};

		float colors[] = {
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w
		};

		unsigned short indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		vertexArray->addBuffer(new VertexBuffer(vertices, sizeof(vertices), 3), 0);
		vertexArray->addBuffer(new VertexBuffer(colors, sizeof(colors), 4), 1);
		indexBuffer = new IndexBuffer(indices, 6);
	}

	StaticSprite::~StaticSprite()
	{
		delete vertexArray;
		delete indexBuffer;
	}
}
