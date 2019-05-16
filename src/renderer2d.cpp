#include "renderer2d.h"
#include "sprite.h"
#include "font.h"

namespace lowg {
	Renderer2D::Renderer2D()
		: indexCount(0)
	{
		init();
	}

	void Renderer2D::init()
	{
		transformationStack.push_back(glm::mat4(1.0f));
		transformationBack = &transformationStack.back();

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
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
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

	void Renderer2D::push(const glm::mat4& matrix, bool override)
	{
		if (override)
			transformationStack.push_back(matrix);
		else
			transformationStack.push_back(transformationStack.back() * matrix);
		transformationBack = &transformationStack.back();
	}

	void Renderer2D::pop()
	{
		if (transformationStack.size() > 1)
			transformationStack.pop_back();
		transformationBack = &transformationStack.back();
	}

	void Renderer2D::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		buffer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer2D::submit(const Sprite* sprite)
	{
		const glm::vec3& position = sprite->position;
		const glm::vec2& size = sprite->getSize();
		const glm::vec4& color = sprite->getColor();
		const std::vector<glm::vec2>& uv = sprite->getUV();
		const unsigned int tid = sprite->getTID();

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
				if (textureSlots.size() >= 15) {
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

	void Renderer2D::drawString(const std::string& text, const glm::vec3 position, const glm::vec4& color, Font* font)
	{
		float ts = 0.0f;
		bool found = false;
		for (unsigned int i = 0; i < textureSlots.size(); i++) {
			if (textureSlots[i] == font->atlas->id) {
				ts = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found) {
			if (textureSlots.size() >= 15) {
				end();
				flush();
				begin();
			}
			textureSlots.push_back(font->atlas->id);
			ts = (float)(textureSlots.size());
		}

		float scaleX = 800.0f / 32.0f;
		float scaleY = 500.0f / 18.0f;

		float x = position.x;

		for (unsigned int i = 0; i < text.length(); i++) {
			texture_glyph_t* glyph = ftgl::texture_font_get_glyph(font->font, text.c_str() + i);
			if (glyph != NULL) {
				if (i > 0) {
					float kerning = ftgl::texture_glyph_get_kerning(glyph, text.c_str() + i - 1);
					x += kerning / scaleX;
				}

				float x0 = x + glyph->offset_x / scaleX;
				float y0 = position.y + glyph->offset_y / scaleY;
				float x1 = x0 + glyph->width / scaleX;
				float y1 = y0 - glyph->height / scaleY;

				float u0 = glyph->s0;
				float v0 = glyph->t0;
				float u1 = glyph->s1;
				float v1 = glyph->t1;

				buffer->vertex = *transformationBack * glm::vec4(x0, y0, 0.0f, 1.0f);
				buffer->uv = glm::vec2(u0, v0);
				buffer->tid = ts;
				buffer->color = color;
				buffer++;

				buffer->vertex = *transformationBack * glm::vec4(x0, y1, 0.0f, 1.0f);
				buffer->uv = glm::vec2(u0, v1);
				buffer->tid = ts;
				buffer->color = color;
				buffer++;

				buffer->vertex = *transformationBack * glm::vec4(x1, y1, 0.0f, 1.0f);
				buffer->uv = glm::vec2(u1, v1);
				buffer->tid = ts;
				buffer->color = color;
				buffer++;

				buffer->vertex = *transformationBack * glm::vec4(x1, y0, 0.0f, 1.0f);
				buffer->uv = glm::vec2(u1, v0);
				buffer->tid = ts;
				buffer->color = color;
				buffer++;

				indexCount += 6;

				x += glyph->advance_x / scaleX;
			}
		}
	}

	void Renderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer2D::flush()
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
		textureSlots.clear();
	}

	Renderer2D::~Renderer2D()
	{
		delete ibo;
		glDeleteBuffers(1, &vbo);
	}
}
