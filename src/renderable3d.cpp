#include "renderable3d.h"
#include <vector>
#include "utils.h"

namespace lowg {
	Renderable3D::Renderable3D(Shader& shader, glm::vec3 position, const char* modelPath, const char* texturePath)
		: Renderable(shader, position)
	{
		load_obj(modelPath, vertices, uvs, normals);

		texture = new Texture(texturePath);
		vertexArray->addBuffer(new VertexBuffer(&vertices[0], vertices.size() * sizeof(glm::vec3), 3), 0);
		vertexArray->addBuffer(new VertexBuffer(&uvs[0], uvs.size() * sizeof(glm::vec2), 2), 1);
	}

	Renderable3D::~Renderable3D()
	{
		delete texture;
	}
}
