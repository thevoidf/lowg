#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.h"
#include "renderer.h"
#include "mat4.h"

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
	glUseProgram(shader_program);

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

	// begin_rectangle(vertices, sizeof(vertices), indices, sizeof(indices), vertex_shader, fragment_shader);

	int projection_location = glGetUniformLocation(shader_program, "pr");
	int view_location = glGetUniformLocation(shader_program, "view");
	int model_location = glGetUniformLocation(shader_program, "model");

	float pr[4*4];
	float view[4*4];
	float model[4*4];

	proj(pr, 45.0f, (float) WIDTH/HEIGHT, 0.1f, 100.0f);
	translate(view, 0.0f, 0.0f, -1.0f);
	translate(model, 0.0f, 0.0f, 0.0f);

	glUniformMatrix4fv(projection_location, 1, GL_FALSE, pr);
	glUniformMatrix4fv(view_location, 1, GL_FALSE, view);
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model);

	begin_triangle(vertices, sizeof(vertices), vertex_shader, fragment_shader);

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		glClearColor(0.2f, 0.1f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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
