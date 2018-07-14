#pragma once

#include <glad/glad.h>
#include "indexbuffer.h"
#include "renderable2d.h"
#include "renderer2d.h"

namespace lowg {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_TEXTURE_INDEX	1
#define SHADER_COLOR_INDEX	2

	class BatchRenderer2D : public Renderer2D
	{
	private:
		unsigned int vao;
		unsigned int vbo;
		IndexBuffer* ibo;
		unsigned int indexCount;
		VertexData* buffer;
	public:
		BatchRenderer2D();
		~BatchRenderer2D();
		void begin();
		void submit(const Renderable2D* renderable) override;
		void end();
		void flush() override;
	private:
		void init();
	};

}
