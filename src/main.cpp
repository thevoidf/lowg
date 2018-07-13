#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "window.h"
#include "shader.h"
#include "vertexarray.h"
#include "renderable2d.h"
#include "staticsprite.h"
#include "sprite.h"
#include "renderable3d.h"
#include "simple2drenderer.h"
#include "simple3drenderer.h"
#include "batchrenderer2d.h"
#include "group.h"
#include "tilelayer.h"

#include <time.h>

#define WIDTH 840
#define HEIGHT 520

#define BATCH_RENDERER

int main(int argc, char* argv[])
{
	using namespace lowg;

	Window window("lowg", WIDTH, HEIGHT);

	Shader* color_shader = new Shader("assets/shaders/color.vert", "assets/shaders/color.frag");
	Shader texture_shader("assets/shaders/texture.vert", "assets/shaders/texture.frag");

	glm::mat4 projection = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	color_shader->enable();
	color_shader->setMatrix4fv("pr", projection);
	color_shader->setMatrix4fv("view", view);
	color_shader->setMatrix4fv("model", model);

	Group* group = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 1.0f, 0.0f)));
	TileLayer layer(color_shader);
	group->add(new Sprite(0.0f, 0.0f, 6.0f, 3.0f, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)));
	group->add(new Sprite(0.5f, 0.5f, 5.0f, 2.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)));

	layer.add(group);

#ifdef RENDER_TILES
	for (float y = -9.0f; y < 9.0f; y += 0.9f) {
		for (float x = -16.0f; x < 16.0f; x += 0.9f) {
			layer.add(new Sprite(x, y, 0.8f, 0.8f, glm::vec4(rand() % 1000 / 1000.0f,  rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1.0f)));
		}
	}
#endif

	double start = glfwGetTime();
	int frames = 0;
	float x = 0.0f, y = 0.0f;
	while (!window.shouldClose()) {
		window.clear(0.2f, 0.1f, 0.5f, 1.0f);

		if (window.isKeyPressed(GLFW_KEY_W))
			y += 0.1f;
		if (window.isKeyPressed(GLFW_KEY_S))
			y -= 0.1f;
		if (window.isKeyPressed(GLFW_KEY_A))
			x -= 0.1f;
		if (window.isKeyPressed(GLFW_KEY_D))
			x += 0.1f;

		glm::vec2 pos = window.getMousePosition();
		glm::vec2 p = glm::vec2((float) (pos.x * 32.0f / WIDTH - 16.0f), (float) (9.0f - pos.y * 18.0f / HEIGHT));

		color_shader->enable();
		color_shader->setMatrix4fv("model", glm::translate(view, glm::vec3(x, y, 0.0f)));
		color_shader->setUniform2f("light_pos", p);

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
