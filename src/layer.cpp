#include "layer.h"

#include "batchrenderer2d.h"

namespace lowg {
	Layer::Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projectionMatrix)
		: renderer(renderer), shader(shader), projectionMatrix(projectionMatrix)
	{
		shader->enable();
		shader->setMatrix4fv("pr", projectionMatrix);
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
