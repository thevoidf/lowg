#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "indexbuffer.h"
#include "freetype-gl/freetype-gl.h"

namespace lowg {
	
	struct VertexData;
	class Sprite;
	class Font;

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TEXTURE_INDEX	2
#define SHADER_COLOR_INDEX	3

	class Renderer2D {
	private:
		unsigned int vao;
		unsigned int vbo;
		IndexBuffer* ibo;
		unsigned int indexCount;
		VertexData* buffer;
		std::vector<unsigned int> textureSlots;
		
		std::vector<glm::mat4> transformationStack;
		glm::mat4 *transformationBack;
	public:
		Renderer2D();
		~Renderer2D();
		
		void push(const glm::mat4& matrix, bool override = false);
		void pop();

		void begin();
		void submit(const Sprite* sprite);
		void drawString(const std::string& text, const glm::vec3 position, const glm::vec4& color, Font* font);
		void end();
		void flush();
	private:
		void init();
	};

}
