#include "sprite.h"
#include "renderer2d.h"

namespace lowg {
	Sprite::Sprite()
	{
		init();
	}
	
	Sprite::Sprite(float x, float y, float width, float height, const glm::vec4& color)
		: Sprite(glm::vec3(x, y, 0.0f), glm::vec2(width, height), color)
	{
	}

	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Sprite(glm::vec3(x, y, 0.0f), glm::vec2(width, height), glm::vec4(1, 1, 1, 1))
	{
		this->texture = texture;
	}

	Sprite::Sprite(glm::vec3 position, glm::vec2 size, glm::vec4 color)
		: position(position), size(size), color(color)
	{
		init();
	}

	void Sprite::submit(Renderer2D* renderer) const
	{
		renderer->submit(this);
	}

	void Sprite::init()
	{
		uvs.push_back(glm::vec2(0.0f, 0.0f));
		uvs.push_back(glm::vec2(0.0f, 1.0f));
		uvs.push_back(glm::vec2(1.0f, 1.0f));
		uvs.push_back(glm::vec2(1.0f, 0.0f));
		texture = nullptr;

		rotation = glm::vec3(0.0f, 0.0f, 1.0f);
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		angle = 0.0f;
	}

	Sprite::~Sprite()
	{
	}
}
