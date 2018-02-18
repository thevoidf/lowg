#include <stdio.h>
#include <stdlib.h>
#include <SOIL/SOIL.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "mat4.h"
#include "vec3.h"
#include "shader.h"
#include "utils.h"
#include <time.h>

#define WIDTH 600
#define HEIGHT 400

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
	GLFWwindow *window;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW/OpenGL", NULL, NULL);
	if (window == NULL) {
		printf("Failed to create window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		printf("Failed to init GLAD");
		return -1;
	}

	float triangle_vertices[] = {
		 1.0f, -1.0f,
		-1.0f, -1.0f,
		 0.0f,	1.0f
	};
	float triangle_colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	float rectangle_vertices[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,	0.5f,
		-0.5f,	0.5f
	};
	GLfloat cube_vertices[] = {
			-1.0f,-1.0f,-1.0f, // triangle 1 : begin
			-1.0f,-1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, // triangle 1 : end
			1.0f, 1.0f,-1.0f, // triangle 2 : begin
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f, // triangle 2 : end
			1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f, 1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,
			1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,
			-1.0f,-1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f, 1.0f,-1.0f,
			1.0f,-1.0f,-1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f,-1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f,-1.0f, 1.0f
	};

	srand((unsigned int) time(NULL));

	int i;
	float cube_colors[400];
	float a = 1.0;
	for (i = 0; i < 400; i++) {
		float r = ((float)rand()/(float)(RAND_MAX)) * a;
		cube_colors[i] = r;
	}

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/*
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	*/

	GLuint shader;
	shader_create_shader_program(&shader, "assets/shaders/shader.vert", "assets/shaders/shader.frag");
	shader_enable(shader);

	int projection_location = glGetUniformLocation(shader, "pr");
	int view_location = glGetUniformLocation(shader, "view");
	int model_location = glGetUniformLocation(shader, "model");

	float pr[4*4];
	float view[4*4];

	mat4_identity(pr);
	mat4_perspective(pr, 45.0f, (float) WIDTH/HEIGHT, 0.1f, 100.0f);
	mat4_identity(view);
	mat4_translate(view, 0.0f, 0.0f, -10.0f);

	float model[4*4];
	float angle = 0.0f;
	vec3 axis = { 0.0f, 1.0f, 0.0f };

	glUniformMatrix4fv(projection_location, 1, GL_FALSE, pr);
	glUniformMatrix4fv(view_location, 1, GL_FALSE, view);

	/* =========== rendering OBJ ============== */

	float *vb;
	size_t num_triangles;
	int stride;

	parse_obj("assets/monkey.obj", &vb, NULL, &stride, &num_triangles);

	float *box_vb, *box_tex;
	size_t box_num;
	int box_stride;

	parse_obj("assets/cube.obj", &box_vb, &box_tex, &box_stride, &box_num);

	float model_colors[9000];
	a = 1.0;
	for (i = 0; i < 9000; i++) {
		float r = ((float)rand()/(float)(RAND_MAX)) * a;
		model_colors[i] = r;
	}

	GLuint triangle_position_buffer = gen_buffer(triangle_vertices, sizeof(triangle_vertices));
	GLuint triangle_color_buffer = gen_buffer(triangle_colors, sizeof(triangle_colors));

	GLuint cube_position_buffer = gen_buffer(cube_vertices, sizeof(cube_vertices));
	GLuint cube_colors_buffer = gen_buffer(cube_colors, sizeof(cube_colors));

	GLuint model_position_buffer = gen_buffer(vb, num_triangles * 3 * stride * sizeof(float));
	GLuint model_color_buffer = gen_buffer(model_colors, sizeof(model_colors));

	GLuint box_position_buffer = gen_buffer(box_vb, box_num * 3 * box_stride * sizeof(float));
	GLuint box_tex_buffer = gen_buffer(box_tex, box_num * 2 * box_stride * sizeof(float));

	float vertices[] = {
	//  Position      Color             Texcoords
			-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
			-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};
	GLuint rectangle_position_buffer = gen_buffer(vertices, sizeof(vertices));

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	float color[] = { 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	float pixels[] = {
		0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

	int width, height;
	unsigned char* image = SOIL_load_image(
										"assets/dark_mount.jpg",
										&width, &height, 0,
										SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
								GL_UNSIGNED_BYTE, image);
	// SOIL_free_image_data(image);

	/* =========== rendering OBJ ============== */

	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		angle -= 1.0f;

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glClearColor(0.2f, 0.1f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// model
		mat4_identity(model);
		mat4_translate(model, -3.0f, 0.0f, 0.0f);
		mat4_rotate(model, angle, axis);
		glUniformMatrix4fv(model_location, 1, GL_FALSE, model);

		render(model_position_buffer, model_color_buffer,
						NULL, 3, 36, 3, sizeof(float) * 3,
						3 * num_triangles, GL_TRIANGLES);

		// cube
		mat4_identity(model);
		mat4_translate(model, 0.0f, 0.0f, 0.0f);
		mat4_rotate(model, angle, axis);
		glUniformMatrix4fv(model_location, 1, GL_FALSE, model);

		// render(cube_position_buffer, cube_colors_buffer,
		// 			NULL, 3, sizeof(float) * 3, 3, sizeof(float) * 3,
		// 			36, GL_TRIANGLES);

		// render(box_position_buffer, model_color_buffer,
		// 				NULL, 3, 36, 3, sizeof(float) * 3,
		// 				3 * box_num, GL_TRIANGLES);

		glBindBuffer(GL_ARRAY_BUFFER, box_position_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
													 36, 0);
		glBindBuffer(GL_ARRAY_BUFFER, box_tex_buffer);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
													1, 0);

		glDrawArrays(GL_TRIANGLES, 0, 3 * box_num);

		// triangle
		mat4_identity(model);
		vec3 axis = { 1.0f, 0.0f, 0.0f };
		vec3 scale = { 10.0f, 6.0f, 0.0f };
		// mat4_rotate(model, 30.0f, axis);
		mat4_translate(model, 0.0f, 0.0f, -1.0f);
		mat4_scale(model, scale);
		glUniformMatrix4fv(model_location, 1, GL_FALSE, model);

		glBindBuffer(GL_ARRAY_BUFFER, rectangle_position_buffer);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
													 7*sizeof(float), 0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
													 7*sizeof(float), (void*)(2*sizeof(float)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
													 7*sizeof(float), (void*)(5*sizeof(float)));

		// glDrawArrays(GL_TRIANGLES, 0, 6 * 2);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

		/* render(rectangle_position_buffer, rectangle_position_buffer,
					indices, 2, sizeof(float) * 2,
					3, sizeof(float) * 3,
					sizeof(indices), GL_POINTS); */

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		printf("EEEEEEEEE\n");
}
