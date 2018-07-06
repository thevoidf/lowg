#include <iostream>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "renderable2d.h"
#include "simplerenderer.h"
#include "texture.h"

namespace lowg {
	void SimpleRenderer::submit(const Renderable* renderable)
	{
		renderQueue.push_back((Renderable2D*) renderable);
	}

	void SimpleRenderer::flush()
	{
		while (!renderQueue.empty()) {
			const Renderable2D* renderable = renderQueue.front();

			Shader& shader = renderable->getShader();
			shader.enable();

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
			glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -30.0f));
			glm::vec2 size = renderable->getSize();
			glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 0.0f)); 
			model = glm::translate(model, renderable->getPosition());

			shader.setMatrix4fv("pr", projection);
			shader.setMatrix4fv("view", view);
			shader.setMatrix4fv("model", model);

			renderable->getVAO()->bind();
			renderable->getIBO()->bind();

			if (renderable->getTexture()) {
				renderable->getTexture()->bind();
				// sampler what?
				// shader.setUniform1f("tex", 0);
			}

			renderable->getShader().setMatrix4fv("model", model);
			glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);

			if (renderable->getTexture())
				renderable->getTexture()->unbind();
			renderable->getVAO()->unbind();
			renderable->getIBO()->unbind();

			shader.disable();

			renderQueue.pop_front();
		}
	}
}
