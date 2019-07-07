#include <iostream>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "renderable3d.h"
#include "renderer3d.h"
#include "texture.h"
#include <GLFW/glfw3.h>

namespace lowg {
	void Renderer3D::submit(const Renderable3D* renderable)
	{
		renderQueue.push_back(renderable);
	}

	void Renderer3D::flush()
	{
		while (!renderQueue.empty()) {
			const Renderable3D* renderable = renderQueue.front();

			Shader& shader = renderable->getShader();

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 500.0f, 0.1f, 100.f);
			glm::mat4 model = glm::mat4(1.0f);

			shader.setMatrix4fv("pr", projection);
			shader.setMatrix4fv("model", model);

			renderable->getVAO()->bind();
			renderable->getTexture()->bind();

			model = glm::scale(model, renderable->scale);
			model = glm::translate(model, renderable->position);
			model = glm::rotate(model, renderable->angle, renderable->rotation);

			renderable->getShader().setMatrix4fv("model", model);
			glDrawArrays(GL_TRIANGLES, 0, renderable->getVertices().size());

			renderable->getTexture()->unbind();
			renderable->getVAO()->unbind();

			renderQueue.pop_front();
		}
	}
}
