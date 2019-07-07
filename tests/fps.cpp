#include "../src/window.h"
#include "../src/shader.h"
#include "../src/renderer2d.h"
#include "../src/layer.h"
#include "../src/sprite.h"
#include "../src/texture.h"
#include "../src/text.h"
#include "../src/renderable3d.h"
#include "../src/renderer3d.h"
#include "../src/fpscamera.h"

#define WIDTH 1280
#define HEIGHT 720

int main()
{
	using namespace lowg;

	Window window("FPS Demo", WIDTH, HEIGHT);
	Shader shader("../assets/shaders/simple.vert", "../assets/shaders/simple.frag");
	FPSCamera camera(glm::vec2(WIDTH, HEIGHT), glm::vec3(0.0f, 0.0f, 0.0f));

	Renderable3D* cube = new Renderable3D(shader, glm::vec3(-3.0f, 0.0f, 0.0f), "../assets/cube.obj", "../assets/snow.jpg");
	Renderable3D* monkey = new Renderable3D(shader, glm::vec3(2.0f, 0.0f, 0.0f), "../assets/monkey.obj", "../assets/tex.jpg");
	Renderable3D* floor = new Renderable3D(shader, glm::vec3(0.0f, -0.1f, 0.0f), "../assets/plane.obj", "../assets/brick.png");
	Renderer3D renderer;

	shader.enable();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	floor->scale = glm::vec3(2.0f, 2.0f, 2.0f);
	cube->scale = glm::vec3(0.2f, 0.2f, 0.2f);
	monkey->scale = glm::vec3(0.2f, 0.2f, 0.2f);

	while (!window.shouldClose()) {
		window.clear(1.0f, 0.0f, 1.0f, 1.0f);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glm::mat4 view = camera.getViewMatrix();
		shader.setMatrix4fv("view", view);

		cube->rotation = glm::vec3(0.0f, 1.0f, 0.0f);
		cube->angle = (float) glfwGetTime();

		camera.update(window, deltaTime);

		renderer.submit(floor);
		renderer.submit(cube);
		renderer.submit(monkey);
		renderer.flush();

		window.update();
		window.syncKeys();
	}

	return 0;
}
