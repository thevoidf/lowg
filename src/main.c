#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "mat4.h"
#include "vec3.h"
#include "shader.h"

#define WIDTH 600
#define HEIGHT 400

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

int main()
{
	// float* res = malloc(sizeof(float)*16);
	// vec3 camera = { 0.0f, 0.0f, 0.0f };
	// vec3 obj = { 0.0f, 0.0f, 0.0f };
	// vec3 up = { 0.0f, 0.0f, 0.0f };
	// mat4_look_at(res, camera, obj, up);
	// mat4_print(res);

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

	GLuint shader;
	shader_create_shader_program(&shader, "assets/shaders/shader.vert", "assets/shaders/shader.frag");
	shader_enable(shader);

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

	int projection_location = glGetUniformLocation(shader, "pr");
	int view_location = glGetUniformLocation(shader, "view");
	int model_location = glGetUniformLocation(shader, "model");

	float pr[4*4];
	float view[4*4];

	mat4_identity(pr);
	mat4_perspective(pr, 45.0f, (float) WIDTH/HEIGHT, 0.1f, 100.0f);
	mat4_identity(view);
	mat4_translate(view, 0.0f, 0.0f, -1.0f);

	float model[4*4];
	float angle = 0.0f;
	mat4_identity(model);
	vec3 axis = { 0.0f, 1.0f, 0.0f };
	mat4_rotate(model, angle, axis);
	mat4_translate(model, 0.4f, 0.0f, 0.0f);

	mat4_print(model);

	glUniformMatrix4fv(projection_location, 1, GL_FALSE, pr);
	glUniformMatrix4fv(view_location, 1, GL_FALSE, view);
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model);

	begin_triangle(vertices, sizeof(vertices));
	// begin_rectangle(vertices, sizeof(vertices), indices, sizeof(indices), vertex_shader, fragment_shader);

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		angle += 1.0f;
		mat4_rotate(model, angle, axis);
		glUniformMatrix4fv(model_location, 1, GL_FALSE, model);

		glClearColor(0.2f, 0.1f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		render(TYPE_TRIANGLE);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shader_disable(shader);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}
