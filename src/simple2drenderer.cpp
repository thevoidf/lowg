#include "simple2drenderer.h"

#include <iostream>

namespace lowg {
	void SimpleRenderer::submit(const Renderable2D* renderable)
	{
		renderQueue.push_back((StaticSprite*) renderable);
	}

	void SimpleRenderer::flush()
	{
		while (!renderQueue.empty()) {
			const StaticSprite* sprite = renderQueue.front();

			sprite->getVAO()->bind();
			sprite->getIBO()->bind();
			sprite->getTexture()->bind();

			// sprite->getShader().setMatrix4fv("model", glm::translate(glm::mat4(1.0f), sprite->getPosition()));
			glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);

			sprite->getVAO()->unbind();
			sprite->getIBO()->unbind();

			renderQueue.pop_front();
		}
	}
}
