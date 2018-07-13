#include "batchrenderer2d.h"

namespace lowg {
	BatchRenderer2D::BatchRenderer2D()
		: indexCount(0)
	{
		init();
	}

	void BatchRenderer2D::init()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		unsigned int* indices = new unsigned int[RENDERER_INDICES_SIZE];

		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			indices[  i  ] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

		glBindVertexArray(0);
	}

	void BatchRenderer2D::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		buffer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::submit(const Renderable2D* renderable)
	{
		const glm::vec3& position = renderable->getPosition();
		const glm::vec2& size = renderable->getSize();
		const glm::vec4& color = renderable->getColor();

		buffer->vertex = *transformationBack * glm::vec4(position.x, position.y, position.z, 1.0f);
		buffer->color = color;
		buffer++;

		buffer->vertex = *transformationBack * glm::vec4(position.x, position.y + size.y, position.z, 1.0f);
		buffer->color = color;
		buffer++;

		buffer->vertex = *transformationBack * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1.0f);
		buffer->color = color;
		buffer++;

		buffer->vertex = *transformationBack * glm::vec4(position.x + size.x, position.y, position.z, 1.0f);
		buffer->color = color;
		buffer++;

		indexCount += 6;
	}

	void BatchRenderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer2D::flush()
	{
		glBindVertexArray(vao);
		ibo->bind();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);

		ibo->unbind();
		glBindVertexArray(0);

		indexCount = 0;
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete ibo;
		glDeleteBuffers(1, &vbo);
	}
}
