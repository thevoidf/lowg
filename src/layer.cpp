#include "layer.h"

#include "renderer2d.h"
#include "shader.h"
#include "sprite.h"

namespace lowg {
	Layer::Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projectionMatrix)
		: renderer(renderer), shader(shader), projectionMatrix(projectionMatrix)
	{
		shader->enable();
		shader->setMatrix4fv("pr", projectionMatrix);
		int texIDs[] = {
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
			11, 12, 13, 14
		};
		shader->setUniform1iv("textures", texIDs, 15);
		shader->disable();
	}

	void Layer::add(Sprite* sprite)
	{
		sprites.push_back(sprite);
	}

	void Layer::remove(void *ptr)
	{
		for (unsigned int i = 0; i < sprites.size(); i++) {
			if (sprites[i] == ptr)
				sprites.erase(sprites.begin() + i);
		}
	}

	void Layer::removeByIndex(unsigned int index)
	{
		sprites.erase(sprites.begin() + index);
	}

	void Layer::render()
	{
		shader->enable();

		renderer->begin();
		for (const Sprite* sprite : sprites)
			sprite->submit(renderer);
		renderer->end();

		renderer->flush();
	}

	Layer::~Layer()
	{
		delete renderer;
		delete shader;
		for (unsigned int i = 0; sprites.size(); i++) {
			delete sprites[i];
		}
	}
}
