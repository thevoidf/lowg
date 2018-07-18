#include "layer.h"

#include "batchrenderer2d.h"

namespace lowg {
	Layer::Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projectionMatrix)
		: renderer(renderer), shader(shader), projectionMatrix(projectionMatrix)
	{
		shader->enable();
		shader->setMatrix4fv("pr", projectionMatrix);
		int texIDs[] = {
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
			11, 12, 13, 14, 15, 16, 17, 18
		};
		shader->setUniform1iv("textures", texIDs, 19);
		shader->disable();
	}

	void Layer::add(Renderable2D* renderable)
	{
		renderables.push_back(renderable);
	}

	void Layer::render()
	{
		shader->enable();

		((BatchRenderer2D*) renderer)->begin();
		for (const Renderable2D* renderable : renderables)
				renderable->submit(((BatchRenderer2D*) renderer));
		((BatchRenderer2D*) renderer)->end();

		renderer->flush();
	}

	Layer::~Layer()
	{
		delete renderer;
		delete shader;
		for (unsigned int i = 0; renderables.size(); i++) {
			delete renderables[i];
		}
	}
}
