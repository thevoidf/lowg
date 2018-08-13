#include <iostream>
#include <vector>
#include <map>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../src/window.h"
#include "../src/shader.h"
#include "../src/vertexbuffer.h"
#include "../src/indexbuffer.h"
#include "../src/vertexarray.h"
#include "../src/texture.h"
#include <time.h>
// #include "freetype-gl/freetype-gl.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#define WIDTH 800
#define HEIGHT 600

struct Character {
	unsigned int textureId;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

std::map<GLchar, Character> characters;
GLuint vao, vbo;

void RenderText(lowg::Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

int main()
{
	using namespace lowg;

	Window window("lowg", WIDTH, HEIGHT);

	Shader shader("shaders/simple.vert", "shaders/simple.frag");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));
	shader.enable();
	shader.setMatrix4fv("projection", projection);

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, "../assets/fonts/Vera.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	VertexArray vao;
	VertexBuffer vbo(0, sizeof(GLfloat) * 6 * 4, 4);
	vao.addBuffer(&vbo, 0);

	// shader, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f)
	float x = 25.0f;
	float y = 25.0f;
	float scale = 1.0f;
	glm::vec4 color(1.0f, 1.0f, 0.0f, 1.0f);
	std::string text = "this is lowg";

	while (!window.shouldClose()) {
		window.clear(0.2f, 0.3f, 0.3f, 1.0f);

		x = (float) WIDTH / 2 - 100.0f;
		y = (float) HEIGHT / 2;

		shader.enable();
		glUniform3f(glGetUniformLocation(shader.getShaderId(), "textColor"), color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		vao.bind();

		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++) {
			Character ch = characters[*c];

			GLfloat xpos = x + ch.bearing.x * scale;
			GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

			GLfloat w = ch.size.x * scale;
			GLfloat h = ch.size.y * scale;
			
			GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },            
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }           
			};
			glBindTexture(GL_TEXTURE_2D, ch.textureId);
			vbo.bind();
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			
			vbo.unbind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			
			x += (ch.advance >> 6) * scale;
		}
		vao.unbind();
		glBindTexture(GL_TEXTURE_2D, 0);

		window.update();
	}
	
	return 0;
}

void RenderText(lowg::Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	shader.enable();
	glUniform3f(glGetUniformLocation(shader.getShaderId(), "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = characters[*c];

		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;
			
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },            
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }           
		};
		glBindTexture(GL_TEXTURE_2D, ch.textureId);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
			
		x += (ch.advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
