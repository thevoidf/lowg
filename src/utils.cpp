#include "utils.h"

namespace lowg {
	char* file_read(const char *path)
	{
		FILE* file = fopen(path, "r");
		int len, end;
		char* buf;

		if (!file)
			printf("failed to open file: %s\n", path);

		fseek(file, 0, SEEK_END);

		len = ftell(file);
		buf = (char*) malloc(len + 1);

		fseek(file, 0, SEEK_SET);
		end = fread(buf, sizeof(char), len, file);

		buf[end] = '\0';

		fclose(file);

		return buf;
	}

	bool load_obj(const char* path, std::vector<glm::vec3>& out_verts,
		std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
	{
		std::vector <unsigned int> vertex_indices;
		std::vector <unsigned int> uv_indices;
		std::vector <unsigned int> normal_indices;

		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;

		FILE *f = fopen(path, "r");
		if (f == NULL) {
			std::cout << "Can't open file %s" << path << std::endl;
			return false;
		}

		while (true) {
			char line_header[128];
			int res = fscanf(f, "%s", line_header);
			if (res == EOF)
				break;

			if (strcmp(line_header, "v") == 0) {
				glm::vec3 vertex;
				fscanf(f, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			} else if (strcmp(line_header, "vt") == 0) {
				glm::vec2 uv;
				fscanf(f, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			} else if (strcmp(line_header, "vn") == 0) {
				glm::vec3 normal;
				fscanf(f, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			} else if (strcmp(line_header, "f") == 0) {
				unsigned int vertex_index[3], uv_index[3], normal_index[3];
				int matches = fscanf(
						f, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
						&vertex_index[0],
						&uv_index[0],
						&normal_index[0],

						&vertex_index[1],
						&uv_index[1],
						&normal_index[1],

						&vertex_index[2],
						&uv_index[2],
						&normal_index[2]
				);

				if (matches != 9) {
					std::cout << "this kind of file not supported\n" << std::endl;
					return false;
				}

				vertex_indices.push_back(vertex_index[0]);
				vertex_indices.push_back(vertex_index[1]);
				vertex_indices.push_back(vertex_index[2]);

				uv_indices.push_back(uv_index[0]);
				uv_indices.push_back(uv_index[1]);
				uv_indices.push_back(uv_index[2]);

				normal_indices.push_back(normal_index[0]);
				normal_indices.push_back(normal_index[1]);
				normal_indices.push_back(normal_index[2]);
			}
		}

		unsigned int i;

		for (i = 0; i < vertex_indices.size(); i++) {
			unsigned int vertex_index = vertex_indices[i];
			glm::vec3 vertex = temp_vertices[vertex_index - 1];
			out_verts.push_back(vertex);
		}

		for (i = 0; i < uv_indices.size(); i++) {
			unsigned int uv_index = uv_indices[i];
			glm::vec2 uv = temp_uvs[uv_index - 1];
			out_uvs.push_back(uv);
		}

		for (i = 0; i < normal_indices.size(); i++) {
			unsigned int normal_index = normal_indices[i];
			glm::vec3 normal = temp_normals[normal_index - 1];
			out_normals.push_back(normal);
		}

		return true;
	}

	BYTE* load_image(const char* path, unsigned int& width, unsigned int& height)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;
		fif = FreeImage_GetFileType(path, 0);

		if(fif == FIF_UNKNOWN) 
			fif = FreeImage_GetFIFFromFilename(path);

		if(fif == FIF_UNKNOWN)
			return nullptr;

		if(FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, path);

		if(!dib)
			return nullptr;

		BYTE* result = FreeImage_GetBits(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);

		return result;
	}
}
