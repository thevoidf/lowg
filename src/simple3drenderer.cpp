#include <iostream>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "renderable3d.h"
#include "simple3drenderer.h"
#include "texture.h"

namespace lowg {
	void Simple3DRenderer::submit(const Renderable* renderable)
	{
		renderQueue.push_back((Renderable3D*) renderable);
	}

	void Simple3DRenderer::flush()
	{
		while (!renderQueue.empty()) {
			const Renderable3D* renderable = renderQueue.front();

			Shader& shader = renderable->getShader();
			shader.enable();

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
			glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
			glm::mat4 model = glm::mat4(1.0f);

			shader.setMatrix4fv("pr", projection);
			shader.setMatrix4fv("view", view);
			shader.setMatrix4fv("model", model);

			renderable->getVAO()->bind();

			renderable->getTexture()->bind();

			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			model = glm::rotate(model, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::translate(model, renderable->getPosition());

			renderable->getShader().setMatrix4fv("model", model);
			glDrawArrays(GL_TRIANGLES, 0, renderable->getVertices().size());

			renderable->getTexture()->unbind();
			renderable->getVAO()->unbind();

			shader.disable();

			renderQueue.pop_front();
		}
	}
}
