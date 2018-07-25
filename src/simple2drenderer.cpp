#include "simple2drenderer.h"

#include <iostream>

namespace lowg {
	void Simple2DRenderer::submit(const Renderable2D* renderable)
	{
		renderQueue.push_back((StaticSprite*) renderable);
	}

	void Simple2DRenderer::flush()
	{
		while (!renderQueue.empty()) {
			const StaticSprite* sprite = renderQueue.front();

			sprite->getShader().enable();
			sprite->getVAO()->bind();
			sprite->getIBO()->bind();
			if (sprite->getTexture())
				sprite->getTexture()->bind();

			sprite->getShader().setMatrix4fv("pr", glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
			sprite->getShader().setMatrix4fv("view", glm::mat4(1.0f));
			sprite->getShader().setMatrix4fv("model", glm::mat4(1.0f));
			
			glm::mat4 trans = glm::scale(glm::mat4(1.0f), sprite->scale);
			trans = glm::rotate(trans, sprite->angle, sprite->rotation);
			trans = glm::translate(trans, sprite->position);

			sprite->getShader().setMatrix4fv("model", trans);
			glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);

			sprite->getVAO()->unbind();
			sprite->getIBO()->unbind();

			renderQueue.pop_front();
		}
	}
}
