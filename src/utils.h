#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <FreeImage.h>

namespace lowg {
	char* file_read(const char *path);
	unsigned int gen_buffer(void* data, unsigned int size);
	bool load_obj(const char* path, std::vector<glm::vec3>& out_verts,
		std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals);
	void load_texture(const char* image_path, int &width,
			int &height, unsigned int &tex);
	BYTE* load_image(const char* path, unsigned int& width, unsigned int& height);
}
