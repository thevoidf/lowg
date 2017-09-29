#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "renderer.h"
#include <math.h>

#define WIDTH 600
#define HEIGHT 400

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW/OpenGL", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		printf("Failed to init GLAD");
		return -1;
	}

	int vertex_shader;
	create_shader(&vertex_shader, GL_VERTEX_SHADER, "assets/shaders/shader.vert", 0);

	int fragment_shader;
	create_shader(&fragment_shader, GL_FRAGMENT_SHADER, "assets/shaders/shader.frag", 0);

	int shader_program;
	create_program(&shader_program, vertex_shader, fragment_shader);

	// vertex data
	float vertices[] = {
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};
// float vertices[] = {
	// 	0.5f, 0.5f, 0.0f,
	// 	0.5f, -0.5f, 0.0f,
	// 	-0.5f, -0.5f, 0.0f,
	// 	-0.5f, 0.5f, 0.0f
	// };
	// unsigned int indices[] = {
	// 	0, 1, 3,
	// 	1, 2, 3
	// };

	begin_triangle(vertices, sizeof(vertices), vertex_shader, fragment_shader);
	// begin_rectangle(vertices, sizeof(vertices), indices, sizeof(indices), vertex_shader, fragment_shader);
	
	float xDir = 0.0f;
	float yDir = 0.0f;
	int vertex_dir_location = glGetUniformLocation(shader_program, "dir");

	glUseProgram(shader_program);
	glUniform3f(vertex_dir_location, xDir, 0.0f, 0.0f);

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClearColor(0.2f, 0.1f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			xDir -= 0.01f;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			xDir += 0.01f;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			yDir += 0.01f;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			yDir -= 0.01f;
		}
		glUniform3f(vertex_dir_location, xDir, yDir, 0.0f);

		glBindVertexArray(vao);
		render(TYPE_TRIANGLE);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}

