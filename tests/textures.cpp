#include "../src/window.h"
#include "../src/renderable2d.h"
#include "../src/batchrenderer2d.h"
#include "../src/shader.h"
#include "../src/layer.h"
#include "../src/sprite.h"
#include "../src/texture.h"
#include "../src/text.h"

#define WIDTH 800
#define HEIGHT 500

int main()
{
	using namespace lowg;

	Window window("lowg", WIDTH, HEIGHT);
	Shader shader("../assets/shaders/texture.vert", "../assets/shaders/texture.frag");

	Layer layer(new BatchRenderer2D(), &shader, glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
	Renderable2D* sprite1 = new Sprite(0.0f, 0.0f, 15.0f, 8.0f, new Texture("../assets/tex.jpg"));
	Renderable2D* sprite2 = new Sprite(-5.0f, -5.0f, 15.0f, 8.0f, new Texture("../assets/snow.jpg"));
	Renderable2D* sprite3 = new Sprite(-15.0f, -8.0f, 5.0f, 5.0f, new Texture("../assets/ship.png", GL_RGBA, GL_BGRA));

	layer.add(sprite1);
	layer.add(sprite2);
	layer.add(sprite3);
	
	while (!window.shouldClose()) {
		window.clear(1.0f, 0.0f, 1.0f, 1.0f);
		
		layer.render();
		
		window.update();
	}
	
	return 0;
}
