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
#include "renderer.h"
#include "renderable2d.h"
#include "staticsprite.h"
#include "sprite.h"
#include "renderable3d.h"
#include "simple2drenderer.h"
#include "simple3drenderer.h"
#include "batchrenderer2d.h"

#include <time.h>

#define WIDTH 600
#define HEIGHT 400

#define BATCH_RENDERER

int main(int argc, char* argv[])
{
	using namespace lowg;

	Window window("lowg", WIDTH, HEIGHT);

	Shader color_shader("assets/shaders/color.vert", "assets/shaders/color.frag");
	Shader texture_shader("assets/shaders/texture.vert", "assets/shaders/texture.frag");

	color_shader.enable();

	glm::mat4 projection = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	color_shader.setMatrix4fv("pr", projection);
	color_shader.setMatrix4fv("view", view);
	color_shader.setMatrix4fv("model", model);

	std::vector<Renderable2D*> sprites;

	for (float y = 0; y < 9.0f; y += 0.1f) {
		for (float x = 0; x < 16.0f; x += 0.1f) {
			sprites.push_back(new
#ifdef BATCH_RENDERER
					Sprite
#else
					StaticSprite
#endif
					(x, y, 0.08f, 0.08f, glm::vec4(rand() % 1000 / 1000.0f, 0.0f, 1.0, 1.0f)
#ifndef BATCH_RENDERER
					 , color_shader
#endif
				 ));
		}
	}

#ifdef BATCH_RENDERER
	Sprite sprite1(8.0f, 5.0f, 4.0f, 4.0f, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	Sprite sprite2(4.0f, 4.0f, 2.0f, 2.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	BatchRenderer2D renderer;
#else
	StaticSprite sprite1(8.0f, 5.0f, 4.0f, 4.0f, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), color_shader);
	StaticSprite sprite2(4.0f, 4.0f, 2.0f, 2.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), color_shader);
	SimpleRenderer renderer;
#endif

	Renderable3D box(texture_shader, glm::vec3(0.0f, 0.0f, 0.0f), "/home/void/cube.obj", "assets/tex.jpg");
	Renderable3D monkey(texture_shader, glm::vec3(0.0f, 0.0f, 0.0f), "/home/void/monkey.obj", "assets/snow.jpg");
	Simple3DRenderer rendere3d;

	float x = 0.0f, y = 0.0f;
	while (!window.shouldClose()) {
		window.clear(0.2f, 0.1f, 0.5f, 1.0f);

#ifdef BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++) {
			renderer.submit(sprites[i]);
		}
#ifdef BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();

		window.update();
	}

	return 0;
}
