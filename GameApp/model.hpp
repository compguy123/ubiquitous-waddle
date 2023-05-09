#pragma once

#include "common.h"
#include "mesh.hpp"

#include <string>
#include <iostream>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stb_image.h>

using std::vector, std::string, std::string_view, std::cout, std::endl;
using glm::vec2, glm::vec3, glm::vec4;

class Model
{
public:
	Model(const char* path)
	{
		LoadModel(path);
	}
	void Draw(const Shader& shader);

private:
	// model data
	vector<Mesh> _meshes;
	string_view _directory;
	vector<Texture> _texturesLoaded;

	void LoadModel(const string_view& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const string_view& typeName);
};


