#pragma once

#include <iostream>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "texture.h"
#include "renderable.h"

namespace lowg {
	class Renderable3D : public Renderable
	{
	protected:
		Texture* texture;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
	public:
		Renderable3D(Shader& shader, glm::vec3 position, const char* modelPath, const char* texturePath);
		virtual ~Renderable3D();

		inline const Texture* getTexture() const { return texture; }
		inline const std::vector<glm::vec3> getVertices() const { return vertices; }
		inline const std::vector<glm::vec2> getUV() const { return uvs; }
		inline const std::vector<glm::vec3> getNormals() const { return normals; }
	};
}
