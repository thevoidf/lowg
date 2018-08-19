#include <iostream>
#include <vector>
#include <map>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../src/window.h"
#include "../src/shader.h"
#include "../src/renderable2d.h"
#include "../src/static_text.h"
#include "../src/staticsprite.h"
#include "../src/simple2drenderer.h"
#include "../src/batchrenderer2d.h"
#include "../src/layer.h"
#include "../src/sprite.h"
#include "../src/text.h"
#include "../src/texture.h"
#include <time.h>
#include "freetype-gl/freetype-gl.h"

#define WIDTH 800
#define HEIGHT 500

#define BATCH 1

int main()
{
	using namespace lowg;

	Window window("lowg", WIDTH, HEIGHT);
	Shader shader(
#if BATCH
    "../assets/shaders/texture.vert",
		"../assets/shaders/texture.frag"
#else
		"../assets/shaders/simple.vert",
		"../assets/shaders/simple.frag"
#endif
	);

#if BATCH
	Layer layer(new BatchRenderer2D(), &shader, glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f));
	Renderable2D* sprite = new Sprite(5.0f, 5.0f, 5.0f, 5.0f, new Texture("../assets/tex.jpg"));
	Renderable2D* sprite2 = new Sprite(-5.0f, -5.0f, 5.0f, 5.0f, new Texture("../assets/snow.jpg"));
	Renderable2D* text = new Text("hello lowggggg 23123123", -10.0f, 2.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	layer.add(sprite);
	layer.add(sprite2);
	layer.add(text);
#else
	Simple2DRenderer renderer;
	StaticText text("static lowg", 100.0f, -100.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), shader);
	StaticSprite sprite(300.0f, 100.0f, 200.0f, 200.0f, "../assets/tex.jpg", shader);
#endif
	while (!window.shouldClose()) {
		window.clear(1.0f, 0.0f, 1.0f, 1.0f);
#if BATCH
		layer.render();
#else
		renderer.submit(&text);
		renderer.submit(&sprite);
		renderer.flush();
#endif
		window.update();
	}
	
	return 0;
}
