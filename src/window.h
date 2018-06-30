#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace lowg {

#define MAX_KEYS 		1024 
#define MAX_BUTTONS 32 

	class Window
	{
	private:
		unsigned int width;
		unsigned int height;
		const char* title;
		GLFWwindow *window;

		bool keys[MAX_KEYS];
		bool mouseButtons[MAX_BUTTONS];
		double mouseX, mouseY; 
	public:
		Window(const char* title, unsigned int width, unsigned int height);
		~Window();
		void update() const;
		bool shouldClose() const;
		void clear(float r, float g, float b, float a) const;

		bool isKeyPressed(unsigned int keyCode) const;
		bool isMouseButtonPressed(unsigned int buttonCode) const;
		glm::vec2 getMousePosition() const;
	private:
		bool init();
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	};
}
