#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../src/window.h"
#include "../src/shader.h"
#include "../src/renderable2d.h"
#include "../src/text.h"
#include "../src/batchrenderer2d.h"
#include "../src/sprite.h"
#include "../src/texture.h"
#include "../src/layer.h"

int main()
{
	using namespace lowg;

	Window window("Fonts", 800, 500);
	Shader shader("../assets/shaders/texture.vert", "../assets/shaders/texture.frag");
	glm::mat4 projection = glm::ortho(0.0f, 10.0f, 0.0f, 10.0f);

	Layer layer(new BatchRenderer2D(), &shader, projection);
	Sprite rect(5.0f, 5.0f, 4.0f, 4.0f, new Texture("../assets/tex.jpg"));
	Text text("Hello lowg", 2.0f, 5.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	layer.add(&rect);
	layer.add(&text);

	while (!window.shouldClose()) {
		window.clear(0.6f, 0.2f, 0.1f, 1.0f);
		layer.render();
		window.update();
	}

	return 0;
}
