#include "batchrenderer2d.h"

#include <iostream>

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
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
		glVertexAttribPointer(SHADER_TEXTURE_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

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
		const std::vector<glm::vec2>& uv = renderable->getUV();
		const unsigned int tid = renderable->getTID();

		float ts = 0.0f;
		if (tid > 0) {
			bool found = false;
			for (unsigned int i = 0; i < textureSlots.size(); i++) {
				if (textureSlots[i] == tid) {
					ts = (float) (i + 1);
					found = true;
					break;
				}
			}

			if (!found) {
				// 32
				if (textureSlots.size() >= 32) {
					end();
					flush();
					begin();
				}
				textureSlots.push_back(tid);
				ts = (float) (textureSlots.size());
			}
		}

		buffer->vertex = *transformationBack * glm::vec4(position.x, position.y, position.z, 1.0f);
		buffer->uv = uv[0];
		buffer->tid = ts;
		buffer->color = color;
		buffer++;

		buffer->vertex = *transformationBack * glm::vec4(position.x, position.y + size.y, position.z, 1.0f);
		buffer->uv = uv[1];
		buffer->tid = ts;
		buffer->color = color;
		buffer++;

		buffer->vertex = *transformationBack * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1.0f);
		buffer->uv = uv[2];
		buffer->tid = ts;
		buffer->color = color;
		buffer++;

		buffer->vertex = *transformationBack * glm::vec4(position.x + size.x, position.y, position.z, 1.0f);
		buffer->uv = uv[3];
		buffer->tid = ts;
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
		for (unsigned int i = 0; i < textureSlots.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
		}
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
