#include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	uint vertex, fragment;
	int success;
	char infoLog[512];

	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// similiar for Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// shader Program
	Id = glCreateProgram();
	glAttachShader(Id, vertex);
	glAttachShader(Id, fragment);
	glLinkProgram(Id);
	// print linking errors if any
	glGetProgramiv(Id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(Id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(Id);
}

void Shader::SetBool(const std::string_view& name, bool value) const
{
	glUniform1i(glGetUniformLocation(Id, name.data()), (int)value);
}

void Shader::SetInt(const std::string_view& name, int value) const
{
	glUniform1i(glGetUniformLocation(Id, name.data()), value);
}

void Shader::SetFloat(const std::string_view& name, float value) const
{
	glUniform1f(glGetUniformLocation(Id, name.data()), value);
}

void Shader::SetVec2(const std::string_view& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(Id, name.data()), 1, &value[0]);
}

void Shader::SetVec2(const std::string_view& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(Id, name.data()), x, y);
}

void Shader::SetVec3(const std::string_view& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(Id, name.data()), 1, &value[0]);
}

void Shader::SetVec3(const std::string_view& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(Id, name.data()), x, y, z);
}

void Shader::SetVec4(const std::string_view& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(Id, name.data()), 1, &value[0]);
}

void Shader::SetVec4(const std::string_view& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(Id, name.data()), x, y, z, w);
}

void Shader::SetMat2(const std::string_view& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(Id, name.data()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string_view& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(Id, name.data()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string_view& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(Id, name.data()), 1, GL_FALSE, &mat[0][0]);
}