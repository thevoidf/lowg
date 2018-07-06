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
#include "renderable3d.h"
#include "simplerenderer.h"
#include "simple3drenderer.h"

#define WIDTH 600
#define HEIGHT 400

int main(int argc, char* argv[])
{
	using namespace lowg;

	Window window("lowg", WIDTH, HEIGHT);

	Shader color_shader("assets/shaders/color.vert", "assets/shaders/color.frag");
	Shader texture_shader("assets/shaders/texture.vert", "assets/shaders/texture.frag");

	Renderable2D sprite1(texture_shader, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(6.0f, 4.0f), "assets/snow.jpg");
	Renderable2D sprite2(color_shader, glm::vec3(-5.0f, -2.0f, 1.0f), glm::vec2(2.0f, 2.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	Renderable3D box(texture_shader, glm::vec3(0.0f, 0.0f, 0.0f), "/home/void/cube.obj", "assets/tex.jpg");
	Renderable3D monkey(texture_shader, glm::vec3(0.0f, 0.0f, 0.0f), "/home/void/monkey.obj", "assets/snow.jpg");

	SimpleRenderer renderer;
	Simple3DRenderer rendere3d;

	float x = 0.0f, y = 0.0f;
	while (!window.shouldClose()) {
		window.clear(0.2f, 0.1f, 0.5f, 1.0f);

		if (window.isKeyPressed(GLFW_KEY_A))
			x -= 0.1f;
		if (window.isKeyPressed(GLFW_KEY_D))
			x += 0.1f;
		if (window.isKeyPressed(GLFW_KEY_W))
			y += 0.1f;
		if (window.isKeyPressed(GLFW_KEY_S))
			y -= 0.1f;
		sprite1.setPosition(glm::vec3(x, y, 0.0f));

		/*
		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.flush();
		*/

		box.setPosition(glm::vec3(x, y, 0.0f));
		rendere3d.submit(&box);
		rendere3d.submit(&monkey);
		rendere3d.flush();

		window.update();
	}

	return 0;
}
