#pragma once
#include "common.h"
#include "shader.hpp"

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using std::vector, std::string, std::string_view;
using glm::vec2, glm::vec3, glm::vec4;

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};

struct Texture {
	uint Id;
	string Type;
	string Path;
};

class Mesh {
public:
	// mesh data
	vector<Vertex> Vertices;
	vector<uint> Indices;
	vector<Texture> Textures;

	Mesh(vector<Vertex> vertices, vector<uint> indices, vector<Texture> textures);
	void Draw(const Shader& shader);

private:
	// render data
	uint VAO, VBO, EBO;

	void SetupMesh();
};