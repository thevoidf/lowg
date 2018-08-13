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
#include <time.h>
#include "freetype-gl/freetype-gl.h"

#define WIDTH 800
#define HEIGHT 500

struct vertex_t {
	float x, y, z;    // position
	float s, t;       // texture
	float r, g, b, a; // color
};

GLuint vao, vbo, ibo;

std::vector<vertex_t> vertexVector;
std::vector<GLuint> indexVector;
texture_atlas_t *atlas;

void add_text(texture_font_t *font, char *text, glm::vec4 *color, glm::vec2 *pen)
{
	size_t i, j;
	float r = color->x, g = color->y, b = color->z, a = color->w;
	for( i = 0; i < strlen(text); ++i )
    {
			texture_glyph_t *glyph = texture_font_get_glyph( font, text + i );
			if( glyph != NULL )
        {
					float kerning =  0.0f;
					if( i > 0)
            {
							kerning = texture_glyph_get_kerning( glyph, text + i - 1 );
            }
					pen->x += kerning;
					// printf("x: %.2f, y: %.2f\n", pen->x, pen->y);
					int x0  = (int)( pen->x + glyph->offset_x );
					int y0  = (int)( pen->y + glyph->offset_y );
					int x1  = (int)( x0 + glyph->width );
					int y1  = (int)( y0 - glyph->height );
					float s0 = glyph->s0;
					float t0 = glyph->t0;
					float s1 = glyph->s1;
					float t1 = glyph->t1;
					GLuint indices[6] = {0,1,2, 0,2,3};
					vertex_t vertices[4] = { { x0,y0,0,  s0,t0,  r,g,b,a },
																	 { x0,y1,0,  s0,t1,  r,g,b,a },
																	 { x1,y1,0,  s1,t1,  r,g,b,a },
																	 { x1,y0,0,  s1,t0,  r,g,b,a } };

					unsigned int vstart = vertexVector.size();
					unsigned int istart = indexVector.size();
					
					for (j = 0; j < 4; j++)
						vertexVector.push_back(vertices[j]);
 					for (j = 0; j < 6; j++)
						indexVector.push_back(indices[j]);
					for (j = 0; j < 6; j++)
						indexVector[istart+j] += vstart;

					pen->x += glyph->advance_x;
        }
    }
}


int main()
{
	using namespace lowg;

	Window window("lowg", WIDTH, HEIGHT);

	size_t i;
	texture_font_t *font = 0;
	atlas = texture_atlas_new( 512, 512, 1 );
	const char * filename = "../assets/fonts/Vera.ttf";
	char * text = "A Quick Brown Fox Jumps Over The Lazy Dog 0123456789";
	glm::vec2 pen(5,400);
	glm::vec4 black(0,0,0,1);
	for( i=7; i < 27; ++i)
    {
			font = texture_font_new_from_file( atlas, i, filename );
			pen.x = 5;
			pen.y -= font->height;
			texture_font_load_glyphs( font, text );
			add_text(font, text, &black, &pen );
			texture_font_delete( font );
    }

	//for (int i = 0; i < 100; i++)
	//printf("i: %d\n", indexVector[i]);

	glGenTextures( 1, &atlas->id );
	glBindTexture( GL_TEXTURE_2D, atlas->id );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RED, atlas->width, atlas->height,
								0, GL_RED, GL_UNSIGNED_BYTE, atlas->data );

	Shader shader("shaders/simple.vert", "shaders/simple.frag");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	
	while (!window.shouldClose()) {
		window.clear(0.2f, 0.3f, 0.3f, 1.0f);

		glClearColor( 1, 1, 1, 1 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		shader.enable();
		glUniform1i(glGetUniformLocation(shader.getShaderId(), "texture"), 0);
		shader.setMatrix4fv("projection", projection);
		shader.setMatrix4fv("view", glm::mat4(1.0f));
		shader.setMatrix4fv("model", glm::mat4(1.0f));

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexVector.size() * sizeof(vertex_t), &vertexVector[0], GL_DYNAMIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexVector.size() * sizeof(GLuint), &indexVector[0], GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		/*
		// attribute vec3 vertex;
		// attribute vec2 tex_coord;
		// attribute vec4 color;

		int vertexLocation = glGetAttribLocation(shader.getShaderId(), "vertex");
		int uvLocation = glGetAttribLocation(shader.getShaderId(), "tex_coord");
		int colorLocation = glGetAttribLocation(shader.getShaderId(), "color");

		printf("vertex: %d, uv: %d, color: %d\n", vertexLocation, uvLocation, colorLocation);
		*/

    glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, 36, (const GLvoid*) 0);
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, 0, 36, (const GLvoid*) 12);
		
    glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, 0, 36, (const GLvoid*) 20);

		// printf("count: %d\n", indexVector.size());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glDrawElements(GL_TRIANGLES, indexVector.size(), GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 100000);
		
		window.update();
	}
	
	return 0;
}
