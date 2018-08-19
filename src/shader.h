#pragma once

#include <glm/mat4x4.hpp>

namespace lowg {
	class Shader {
	private:
		unsigned int shaderId;
		unsigned int vertexShader;
		unsigned int fragmentShader;
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shader();

		void enable() const;
		void disable() const;

		static int createShader(const int type, const char* sourcePath);
		static int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

		int getUniformLocation(const char* name);

		void setUniform1i(const char* name, int value);
		void setUniform1f(const char* name, float value);
		void setUniform2f(const char* name, glm::vec2& vec);
		void setUniform1iv(const char* name, int* value, int count);
		void setMatrix4fv(const char* name, glm::mat4 matrix);
		unsigned int getShaderId() const { return this->shaderId; }
	};
}
