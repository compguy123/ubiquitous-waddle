#pragma once

#include "common.h"

//#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <optional>
#include <filesystem>
#include <algorithm>

using std::cout, std::cerr, std::endl, std::vector, std::string, std::string_view, std::optional, std::nullopt;
using glm::vec2, glm::vec3, glm::vec4, glm::mat2, glm::mat3, glm::mat4;

struct ShaderFileInfo
{
	string_view Path;
	int Type;
	string_view TypeName;
	ShaderFileInfo(const string_view& path, optional<int> type = nullopt);
	const string_view GetTypeName(optional<string_view> defaultName = nullopt);
};

class Shader
{
public:
	// the program ID
	uint Id;

	// constructor reads and builds the shader
	Shader(vector<ShaderFileInfo> shaderFileInfos);
	// use/activate the shader
	void Use();
	// utility uniform functions
	void SetBool(const string_view& name, bool value) const;
	void SetInt(const string_view& name, int value) const;
	void SetFloat(const string_view& name, float value) const;
	void SetVec2(const string_view& name, const vec2& value) const;
	void SetVec2(const string_view& name, float x, float y) const;
	void SetVec3(const string_view& name, const vec3& value) const;
	void SetVec3(const string_view& name, float x, float y, float z) const;
	void SetVec4(const string_view& name, const vec4& value) const;
	void SetVec4(const string_view& name, float x, float y, float z, float w) const;
	void SetMat2(const string_view& name, const mat2& mat) const;
	void SetMat3(const string_view& name, const mat3& mat) const;
	void SetMat4(const string_view& name, const mat4& mat) const;
};
