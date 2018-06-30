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
#include "simplerenderer.h"

#define WIDTH 600
#define HEIGHT 400

int main(int argc, char* argv[])
{
	using namespace lowg;

	Window window("lowg", WIDTH, HEIGHT);

	Shader color_shader("assets/shaders/color.vert", "assets/shaders/color.frag");
	Shader texture_shader("assets/shaders/texture.vert", "assets/shaders/texture.frag");

	Renderable sprite1(texture_shader, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(6.0f, 4.0f), "assets/snow.jpg");
	Renderable sprite2(color_shader, glm::vec3(-5.0f, -2.0f, 1.0f), glm::vec2(2.0f, 2.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

	SimpleRenderer renderer;

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

		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.flush();

		window.update();
	}

	return 0;
}
