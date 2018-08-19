#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../src/window.h"
#include "../src/shader.h"
#include "../src/renderable2d.h"
#include "../src/batchrenderer2d.h"
#include "../src/layer.h"
#include "../src/sprite.h"
#include "../src/text.h"
#include "../src/texture.h"
#include <time.h>

#define WIDTH 800
#define HEIGHT 500

int main()
{
	using namespace lowg;

	Window window("lowg", WIDTH, HEIGHT);
	Shader shader("../assets/shaders/texture.vert", "../assets/shaders/texture.frag");

	Layer layer(new BatchRenderer2D(), &shader, glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f));
	Renderable2D* sprite = new Sprite(-12.0f, -2.0f, 15.0f, 8.0f, new Texture("../assets/tex.jpg"));
	Renderable2D* text = new Text("hello lowg 12345", -5.0f, -5.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	Renderable2D* text2 = new Text("hello lowg 12345", 0.0f, -7.0f, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	layer.add(sprite);
	layer.add(text);
	layer.add(text2);
	
	while (!window.shouldClose()) {
		window.clear(1.0f, 0.0f, 1.0f, 1.0f);
		
		layer.render();
		
		window.update();
	}
	
	return 0;
}
