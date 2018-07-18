#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "window.h"
#include "shader.h"
#include "batchrenderer2d.h"
#include "sprite.h"
#include "group.h"
#include "layer.h"
#include "texture.h"

#define WIDTH 840
#define HEIGHT 520

#define BATCH_RENDERER

int main(int argc, char* argv[])
{
	using namespace lowg;

	Window window("lowg", WIDTH, HEIGHT);

	Shader* color_shader = new Shader("assets/shaders/color.vert", "assets/shaders/color.frag");
	Shader* texture_shader = new Shader("assets/shaders/texture.vert", "assets/shaders/texture.frag");

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	texture_shader->enable();
	texture_shader->setMatrix4fv("view", view);
	texture_shader->setMatrix4fv("model", model);

	Layer layer(new BatchRenderer2D(),  texture_shader, glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	Sprite* ship = new Sprite(0, -5, 4, 4, new Texture("/home/void/Pictures/ship.png"));
	layer.add(ship);

	std::vector<Sprite*> projectiles;

#ifdef RENDER_TILES
	for (float y = -9.0f; y < 9.0f; y += 2.0f) {
		for (float x = -16.0f; x < 16.0f; x += 2.0f) {
			layer.add(new Sprite(x, y, 1.9f, 1.9f, glm::vec4(rand() % 1000 / 1000.0f,  rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1.0f)));
		}
	}
#endif

	double start = glfwGetTime();
	int frames = 0;
	while (!window.shouldClose()) {
		window.clear(0.2f, 0.1f, 0.5f, 0.0f);

		if (window.isKeyPressed(GLFW_KEY_W))
			ship->position.y += 0.2f;
		if (window.isKeyPressed(GLFW_KEY_S))
			ship->position.y -= 0.2f;
		if (window.isKeyPressed(GLFW_KEY_A))
			ship->position.x -= 0.2f;
		if (window.isKeyPressed(GLFW_KEY_D))
			ship->position.x += 0.2f;

		if (window.isKeyDown(GLFW_KEY_SPACE)) {
			layer.add(new Sprite(ship->position.x + 1.0f, ship->position.y + 3.0f, 1.5f, 1.5f, new Texture("/home/void/Pictures/ship.png")));
		}

		for (unsigned int i = 0; i < layer.getRenderables().size(); i++) {
			if (i == 0) continue;
			Sprite* projectile = (Sprite*) layer.getRenderables()[i];
			projectile->position.y += 0.4f;

			if (projectile->position.y > 8.0f) {
				layer.remove(i);
			}
		}

		// printf("projectiles: %d\n", layer.getRenderables().size() - 1);

		layer.render();

		frames++;
		if (glfwGetTime() - start >= 1.0) {
			printf("%d frames\n", frames);
			frames = 0;
			start += 1.0;
		}

		window.update();
	}

	return 0;
}
