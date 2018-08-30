#pragma once

#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace lowg {

	class Renderer2D;
	class Shader;
	class Sprite;
	
	class Layer
	{
	protected:
		Renderer2D* renderer;
		std::vector<Sprite*> sprites;
		Shader* shader;
		glm::mat4 projectionMatrix;
	public:
		Layer();
		Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projectionMatrix);
	public:
		virtual ~Layer();
		virtual void add(Sprite* sprite);
		virtual void remove(void *ptr);
		virtual void removeByIndex(unsigned int index);
		virtual void render();
		std::vector<Sprite*> getSprites() { return sprites; }
	};
}
