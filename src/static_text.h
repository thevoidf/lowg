#pragma once

#include "renderable2d.h"
#include "shader.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "renderable2d.h"
#include "freetype-gl/freetype-gl.h"

namespace lowg {
	struct vertex_t {
		float x, y, z;
		float s, t;
		float r, g, b, a;
	};

	class StaticText : public Renderable2D {
	public:
		const char* text;
		unsigned int vao;
		unsigned int vbo;
		unsigned int ibo;
		std::vector<vertex_t> vertexVector;
		std::vector<unsigned int> indexVector;
		Shader& shader;
		ftgl::texture_atlas_t *atlas;
		ftgl::texture_font_t *font;
		VertexArray* vertexArray;
		VertexBuffer* buffer;
		IndexBuffer* indexBuffer;
	public:
		StaticText(const char* text, float x, float y, glm::vec4 color, Shader& shader);

		inline Shader& getShader() const { return shader; }
	};
}
