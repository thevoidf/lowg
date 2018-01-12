#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "util.h"
#include "renderer.h"

#define WIDTH 600
#define HEIGHT 400

#define M_PI 3.14159265358979323846

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

float to_radians(float deg)
{
	return (float) (deg * (M_PI / 180.0f));
}

void normalize(float elements[])
{
	int i;
	for (i = 0; i < 4*4; i++)
		elements[i] = 0.0f;

	elements[0 + 0 * 4] = 1.0f;
	elements[1 + 1 * 4] = 1.0f;
	elements[2 + 2 * 4] = 1.0f;
	elements[3 + 3 * 4] = 1.0f;
}

void
proj(float elements[],
		float fov,
		float aspect_ratio,
		float near,
		float far)
{
	normalize(elements);

	float q = 1.0f / tan(to_radians(0.5f * fov));
	float a = q / aspect_ratio;

	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	elements[0 + 0 * 4] = a;
	elements[1 + 1 * 4] = q;
	elements[2 + 2 * 4] = b;
	elements[3 + 2 * 4] = -1.0f;
	elements[2 + 3 * 4] = c;
}

void
translate(float elements[], float x, float y, float z)
{
	normalize(elements);

	elements[0 + 3 * 4] = x;
	elements[1 + 3 * 4] = y;
	elements[2 + 3 * 4] = z;
}

int main()
{
	float delta = 0.0f;
	float p[4*4];
	int i;

	normalize(p);
	printf("norm:\n");
	for (i=0;i<4*4;i++)
		printf("%f, ", p[i]);
	printf("\n");

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

	printf("proj:\n");
	for (i = 0; i < 4*4; i++)
		printf("%f, ", pr[i]);
	printf("\n");
	printf("trans:\n");
	for (i = 0; i < 4*4; i++)
		printf("%f, ", view[i]);
	printf("\n");
	printf("model:\n");
	for (i = 0; i < 4*4; i++)
		printf("%f, ", model[i]);
	printf("\n");

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
