#include "static_text.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace lowg {
	StaticText::StaticText(const char* text, float x, float y, glm::vec4 color, Shader& shader)
		: Renderable2D(glm::vec3(x, y, 0.0f), glm::vec2(0.0f, 0.0f), color), shader(shader), text(text)
	{
		type = TEXT;
		size_t i, j;
		float r = color.x, g = color.y, b = color.z, a = color.w;
		const char * filename = "../assets/fonts/Vera.ttf";
		glm::vec2 pen(5,400);
		glm::vec4 black(0,0,0,1);
		
		atlas = texture_atlas_new( 512, 512, 1 );
		font = texture_font_new_from_file( atlas, 27, filename );
		texture_font_load_glyphs( font, text );

		pen.x = 5;
		pen.y -= font->height;
		
		for( i = 0; i < strlen(text); ++i ) {
			texture_glyph_t *glyph = texture_font_get_glyph( font, text + i );
			if( glyph != NULL ) {
				float kerning =  0.0f;
				if( i > 0)
					kerning = texture_glyph_get_kerning( glyph, text + i - 1 );
				pen.x += kerning;
				int x0  = (int)( pen.x + glyph->offset_x );
				int y0  = (int)( pen.y + glyph->offset_y );
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

				pen.x += glyph->advance_x;
			}
		}

		texture_font_delete( font );

		glGenTextures( 1, &atlas->id );
		glBindTexture( GL_TEXTURE_2D, atlas->id );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RED, atlas->width, atlas->height,
									0, GL_RED, GL_UNSIGNED_BYTE, atlas->data );
		glBindTexture( GL_TEXTURE_2D, 0);

		/*
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ibo);
		*/

		shader.enable();
		glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 500.0f);
		glUniform1i(glGetUniformLocation(shader.getShaderId(), "texture"), 0);
		shader.setMatrix4fv("pr", projection);
		shader.setMatrix4fv("view", glm::mat4(1.0f));
		shader.setMatrix4fv("model", glm::mat4(1.0f));

		/*
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexVector.size() * sizeof(vertex_t), &vertexVector[0], GL_DYNAMIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, 36, (const GLvoid*) 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, 0, 36, (const GLvoid*) 12);
    glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, 0, 36, (const GLvoid*) 20);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexVector.size() * sizeof(GLuint), &indexVector[0], GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		*/

		vertexArray = new VertexArray();
		buffer = new VertexBuffer(&vertexVector[0], vertexVector.size() * sizeof(vertex_t), 3);
		indexBuffer = new IndexBuffer(&indexVector[0], indexVector.size());

		vertexArray->attribPointer(buffer, 0, 3, GL_FLOAT, 36, 0);
		vertexArray->attribPointer(buffer, 1, 2, GL_FLOAT, 36, 12);
		vertexArray->attribPointer(buffer, 2, 4, GL_FLOAT, 36, 20);
		indexBuffer->unbind();
	}
}
