#include "shader.h"
#include "utils.h"
#include <iostream>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>

namespace lowg {
	Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		this->vertexShader = Shader::createShader(GL_VERTEX_SHADER, vertexShaderPath);
		this->fragmentShader = Shader::createShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

		this->shaderId = Shader::createShaderProgram(this->vertexShader, this->fragmentShader);
	}

	void Shader::enable() const
	{
		glUseProgram(this->shaderId);
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}

	int Shader::createShader(const int type, const char* sourcePath)
	{
		unsigned int shader;
		int success;
		char infoLog[512];

		if (type == GL_VERTEX_SHADER) {
			shader = glCreateShader(GL_VERTEX_SHADER);
		} else if (type == GL_FRAGMENT_SHADER) {
			shader = glCreateShader(GL_FRAGMENT_SHADER);
		}

		const char* shaderSource = file_read(sourcePath);
		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;
			return -1;
		}

		return shader;
	}

	int Shader::createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
	{
		unsigned shaderId;
		int success;
		char infoLog[512];

		shaderId = glCreateProgram();
		glAttachShader(shaderId, vertexShader);
		glAttachShader(shaderId, fragmentShader);
		glLinkProgram(shaderId);

		glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;
			return -1;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderId;
	}

	void Shader::setUniform1f(const char* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setMatrix4fv(const char* name, glm::mat4 matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	int Shader::getUniformLocation(const char* name)
	{
		int location = glGetUniformLocation(shaderId, name);
		if (location == -1)
			std::cout << "Uniform " << name << " not found" << std::endl;
		return location;
	}

	Shader::~Shader()
	{
		this->disable();
		glDeleteProgram(this->shaderId);
	}
}
