#pragma once

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "shader.h"
#include "vertexarray.h"
#include "texture.h"

namespace lowg {
	class Renderable3D
	{
	protected:
		Shader& shader;
		VertexArray* vertexArray;
		Texture* texture;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
	public:
		glm::vec3 scale;
		glm::vec3 position;
		glm::vec3 rotation;
		float angle;
	public:
		Renderable3D(Shader& shader, glm::vec3 position, const char* modelPath, const char* texturePath);
		virtual ~Renderable3D();

		inline const VertexArray* getVAO() const { return vertexArray; }
		inline Shader& getShader() const { return shader; }
		inline const Texture* getTexture() const { return texture; }

		inline const std::vector<glm::vec3> getVertices() const { return vertices; }
		inline const std::vector<glm::vec2> getUV() const { return uvs; }
		inline const std::vector<glm::vec3> getNormals() const { return normals; }
	};
}
