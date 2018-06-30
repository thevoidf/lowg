#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "renderable.h"
#include "simplerenderer.h"

void SimpleRenderer::submit(const Renderable* renderable)
{
	renderQueue.push_back(renderable);
}

void SimpleRenderer::flush()
{
	while (!renderQueue.empty()) {
		const Renderable* renderable = renderQueue.front();
		renderable->getVAO()->bind();
		renderable->getIBO()->bind();

		glm::vec2 size = renderable->getSize();
		glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 0.0f)); 
		model = glm::translate(model, renderable->getPosition());

		renderable->getShader().setMatrix4fv("model", model);
		glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);

		renderable->getVAO()->unbind();
		renderable->getIBO()->unbind();

		renderQueue.pop_front();
	}
}
