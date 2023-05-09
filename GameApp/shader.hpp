#pragma once

#include "common.h"

//#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// the program ID
	uint Id;

	// constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	// use/activate the shader
	void Use();
	// utility uniform functions
	void SetBool(const std::string_view& name, bool value) const;
	void SetInt(const std::string_view& name, int value) const;
	void SetFloat(const std::string_view& name, float value) const;
	void SetVec2(const std::string_view& name, const glm::vec2& value) const;
	void SetVec2(const std::string_view& name, float x, float y) const;
	void SetVec3(const std::string_view& name, const glm::vec3& value) const;
	void SetVec3(const std::string_view& name, float x, float y, float z) const;
	void SetVec4(const std::string_view& name, const glm::vec4& value) const;
	void SetVec4(const std::string_view& name, float x, float y, float z, float w) const;
	void SetMat2(const std::string_view& name, const glm::mat2& mat) const;
	void SetMat3(const std::string_view& name, const glm::mat3& mat) const;
	void SetMat4(const std::string_view& name, const glm::mat4& mat) const;
};
