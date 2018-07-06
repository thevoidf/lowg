#include "renderable2d.h"

namespace lowg {
	Renderable2D::Renderable2D(Shader& shader, glm::vec3 position, glm::vec2 size)
		: Renderable(shader, position), size(size)
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

		vertexArray->addBuffer(new VertexBuffer(vertices, sizeof(vertices), 3), 0);
	}

	Renderable2D::Renderable2D(Shader& shader, glm::vec3 position, glm::vec2 size, glm::vec4 color)
		: Renderable2D(shader, position, size)
	{
		float colors[] = {
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w
		};

		vertexArray->addBuffer(new VertexBuffer(colors, sizeof(colors), 4), 1);
	}

	Renderable2D::Renderable2D(Shader& shader, glm::vec3 position, glm::vec2 size, const char* texture_path)
		: Renderable2D(shader, position, size)
	{
		float texCoords[] = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		};

		texture = new Texture(texture_path);
		vertexArray->addBuffer(new VertexBuffer(texCoords, sizeof(texCoords), 2), 1);
	}

	Renderable2D::~Renderable2D()
	{
		delete indexBuffer;
		delete texture;
	}
}
