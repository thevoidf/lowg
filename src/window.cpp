#include "window.h"
#include <iostream>

namespace lowg {
	Window::Window(const char* title, unsigned int width, unsigned int height)
	{
		this->title = title;
		this->width = width;
		this->height = height;

		if (!init())
			glfwTerminate();

		int i;
		for (i = 0; i < MAX_KEYS; i++) {
			keys[i] = false;
		}
		for (i = 0; i < MAX_BUTTONS; i++) {
			mouseButtons[i] = false;
		}
	}

	bool Window::init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
		if (this->window == NULL) {
			std::cout << "Failed to create window" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, this);

		glfwSetKeyCallback(window, keyCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetCursorPosCallback(window, mousePositionCallback);
		glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
			std::cout << "Failed to init OpenGL" << std::endl;
			return false;
		}

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

		return true;
	}

	void Window::update() const
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;
		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(this->window);
	}

	void Window::clear(float r, float g, float b, float a) const
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->keys[key] = action != GLFW_RELEASE;
	}

	void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->mouseButtons[button] = action != GLFW_RELEASE;
	}

	void Window::mousePositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->mouseX = xpos;
		win->mouseY = ypos;
	}

	void Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	bool Window::isKeyPressed(unsigned int keyCode) const
	{
		if (keyCode > MAX_KEYS)
			return false;
		return keys[keyCode];
	}

	bool Window::isMouseButtonPressed(unsigned int buttonCode) const
	{
		if (buttonCode > MAX_BUTTONS)
			return false;
		return mouseButtons[buttonCode];
	}

	glm::vec2 Window::getMousePosition() const
	{
		return glm::vec2(mouseX, mouseY);
	}

	Window::~Window()
	{
		glfwTerminate();
	}
}