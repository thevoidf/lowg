#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "window.h"
#include "shader.h"
#include "renderable2d.h"
#include "staticsprite.h"
#include "sprite.h"
#include "simple2drenderer.h"
#include "batchrenderer2d.h"
#include "texture.h"
#include "layer.h"
#include <time.h>

#define WIDTH 620
#define HEIGHT 420

bool aabb(lowg::Renderable2D a, lowg::Renderable2D b)
{
	return a.position.x < b.position.x + b.getSize().x &&
			a.position.x + a.getSize().x > b.position.x &&
			a.position.y < b.position.y + b.getSize().y &&
			a.getSize().y + a.position.y > b.position.y;
}

int main(int argc, char* argv[])
{
	using namespace lowg;

	Window window("lowg", WIDTH, HEIGHT);

	Shader* shader = new Shader("assets/shaders/texture.vert", "assets/shaders/texture.frag");

	Renderable2D* ship = new Sprite(0.0f, -7.0f, 3.0f, 3.0f, new Texture("/home/void/Pictures/ship.png"));

	Layer layer(new BatchRenderer2D(), shader, glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
	layer.add(ship);
	
	std::vector<Renderable2D*> enemies;
	std::vector<Renderable2D*> projectiles;
	std::vector<Renderable2D*> particles;
	
	srand(time(NULL));

	double start = glfwGetTime();
	int frames = 0;
	bool gameOver = false;
	while (!window.shouldClose()) {
		window.clear(0.0f, 0.0f, 0.0f, 0.0f);

		if (window.isKeyPressed(GLFW_KEY_W))
			ship->position.y += 0.3f;
		if (window.isKeyPressed(GLFW_KEY_S))
			ship->position.y -= 0.3f;
		if (window.isKeyPressed(GLFW_KEY_A))
			ship->position.x -= 0.3f;
		if (window.isKeyPressed(GLFW_KEY_D))
			ship->position.x += 0.3f;
		if (window.isKeyDown(GLFW_KEY_SPACE)) {
			Renderable2D* projectile = new Sprite(ship->position.x + 1.0f, ship->position.y + 3.0f, 1.5f, 1.5f, new Texture("/home/void/Pictures/ship.png"));
			projectiles.push_back(projectile);
			layer.add(projectile);
		}

		int x = rand() % (16 * 2) - 16;
		int y = rand() % (9 * 2) - 9;
		Renderable2D* particle = new Sprite(x, y, 0.1f, 0.1f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		particles.push_back(particle);
		layer.add(particle);

		for (unsigned int i = 0; i < particles.size(); i++) {
			Renderable2D* particle = particles[i];
			float xa = 2.0f * ((float) rand() / (float) RAND_MAX) - 1.0f;
			float yas = rand() % 1000 / 1000.0f;

			particle->position.x += xa / 10.0f;
			particle->position.y += yas / 10.0f;
			
			if (particle->position.y >= 9.0f) {
				layer.remove(particle);
				particles.erase(particles.begin() + i);
			}
		}

		for (unsigned int i = 0; i < projectiles.size(); i++) {
			Renderable2D* projectile = projectiles[i];

			projectile->position.y += 0.4f;

			if (projectile->position.y > 8.0f) {
				layer.remove(projectiles[i]);
				projectiles.erase(projectiles.begin() + i);
			}
		}

		for (unsigned int i = 0; i < enemies.size(); i++) {
			Renderable2D* enemy = enemies[i];

			if (!gameOver)
				enemy->position.y -= 0.1f;

			if (enemy->position.y < -10.0f) {
				layer.remove(enemy);
				enemies.erase(enemies.begin() + i);
			}
		}

		for (unsigned int i = 0; i < enemies.size(); i++) {
			for (unsigned int j = 0; j < projectiles.size(); j++) {
				if (aabb(*enemies[i], *projectiles[j])) {
					layer.remove(enemies[i]);
					layer.remove(projectiles[j]);
					enemies.erase(enemies.begin() + i);
					projectiles.erase(projectiles.begin() + j);
				}
			}
		}

		for (unsigned int i = 0; i < enemies.size(); i++) {
			if (aabb(*ship, *enemies[i])) {
				layer.remove(ship);
				layer.remove(enemies[i]);
				enemies.erase(enemies.begin() + i);
				gameOver = true;
			}
		}

		layer.render();

		frames++;

		if (glfwGetTime() - start >= 1.0) {
			if (!gameOver) {
				int enemyX = rand() % 16 + (4 - 16);
				Renderable2D* enemy = new Sprite(enemyX, 8.0f, 3.0f, 3.0f, new Texture("/home/void/Pictures/ship.png"));
				enemies.push_back(enemy);
				layer.add(enemy);
			}

			printf("%d frames\n", frames);
			frames = 0;
			start += 1.0;
		}

		window.update();
	}

	return 0;
}
