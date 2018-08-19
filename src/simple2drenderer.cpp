#include "simple2drenderer.h"

#include <iostream>

namespace lowg {
	void Simple2DRenderer::submit(const Renderable2D* renderable)
	{
		renderQueue.push_back(renderable);
	}

	void Simple2DRenderer::flush()
	{
		while (!renderQueue.empty()) {
			const Renderable2D* renderable = renderQueue.front();

			if (renderable->type == SPRITE) {
				StaticSprite* sprite = (StaticSprite*) renderable;
				
				sprite->getShader().enable();
				sprite->getShader().setMatrix4fv("model", glm::translate(glm::mat4(1.0f), glm::vec3(renderable->position.x, renderable->position.y, 0.0f)));
				sprite->getVAO()->bind();
				sprite->getIBO()->bind();
				
				if (sprite->getTexture())
					sprite->getTexture()->bind();
				
				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_INT, 0);
			} else if (renderable->type == TEXT) {
				StaticText* text = (StaticText*) renderable;
				text->shader.enable();
				text->shader.setMatrix4fv("model", glm::translate(glm::mat4(1.0f), glm::vec3(renderable->position.x, renderable->position.y, 0.0f)));
				glBindTexture(GL_TEXTURE_2D, text->atlas->id);
				text->vertexArray->bind();
				text->buffer->bind();
				text->indexBuffer->bind();
				glDrawElements(GL_TRIANGLES, text->indexVector.size(), GL_UNSIGNED_INT, 0);
			}

			renderQueue.pop_front();
		}
	}
}
