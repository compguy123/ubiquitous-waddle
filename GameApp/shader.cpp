#include "shader.hpp"

bool IsValidShaderType(int type) {
	switch (type)
	{
	case GL_VERTEX_SHADER:
	case GL_FRAGMENT_SHADER:
	case GL_TESS_CONTROL_SHADER:
	case GL_TESS_EVALUATION_SHADER:
		return true;

	default: return false;
	}
}

int GetShaderOrder(int type) {

	switch (type)
	{
	case GL_VERTEX_SHADER: return 0;
	case GL_FRAGMENT_SHADER: return 1;
	case GL_TESS_CONTROL_SHADER: return 2;
	case GL_TESS_EVALUATION_SHADER:return 3;
	default:
		string msg("GetShaderOrder - Provided an invalid type.");
		cerr << msg << " - " << type << endl;
		throw std::invalid_argument(msg);
	}
}

bool ShaderOrdering(const ShaderFileInfo& a, const ShaderFileInfo& b) {
	return GetShaderOrder(a.Type) < GetShaderOrder(b.Type);
}

ShaderFileInfo::ShaderFileInfo(const string_view& path, optional<int> type)
{
	if (!std::filesystem::exists(path))
	{
		string msg("ShaderFileInfo - ctor - Provided path doesn't exist.");
		cerr << msg << " - " << path << endl;
		throw std::invalid_argument(msg);
	}

	if (!type.has_value())
	{
		string upperPath(path);
		transform(upperPath.begin(), upperPath.end(), upperPath.begin(), ::toupper);


		if (upperPath.ends_with(".VERT.GLSL"))
			type = GL_VERTEX_SHADER;
		else if (upperPath.ends_with(".FRAG.GLSL"))
			type = GL_FRAGMENT_SHADER;
		else if (upperPath.ends_with(".COMP.GLSL"))
			type = GL_COMPUTE_SHADER;
		else if (upperPath.ends_with(".GEOM.GLSL"))
			type = GL_GEOMETRY_SHADER;
		else if (upperPath.ends_with(".TESC.GLSL"))
			type = GL_TESS_CONTROL_SHADER;
		else if (upperPath.ends_with(".TESE.GLSL"))
			type = GL_TESS_EVALUATION_SHADER;
		else
		{
			string msg("ShaderFileInfo - ctor - Couldn't determine the type by path.");
			cerr << msg << " - " << path << endl;
			throw std::invalid_argument(msg);
		}
	}

	if (!IsValidShaderType(type.value()))
	{
		string msg("ShaderFileInfo - ctor - Provided type isn't a valid shader type.");
		cerr << msg << " - " << type.value() << endl;
		throw std::invalid_argument(msg);
	}

	Path = path;
	Type = type.value();
}

const string_view ShaderFileInfo::GetTypeName(optional<string_view> defaultName)
{
	switch (Type)
	{
	case GL_VERTEX_SHADER: return "VERTEX";
	case GL_FRAGMENT_SHADER: return "FRAGMENT";
	case GL_TESS_CONTROL_SHADER: return "TESS-CONT";
	case GL_TESS_EVALUATION_SHADER: return "TESS-EVAL";
	default: return defaultName.value_or("<UNKNOWN>");
	}
}

Shader::Shader(vector<ShaderFileInfo> shaderFileInfos) : Id(0)
{
	std::sort(shaderFileInfos.begin(), shaderFileInfos.end(), ShaderOrdering);
	for (ShaderFileInfo& shaderFileInfo : shaderFileInfos)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		string_view shaderTypeName = shaderFileInfo.GetTypeName();
		string sourceCode;
		std::ifstream fileStream;
		// ensure ifstream objects can throw exceptions:
		fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			fileStream.open(shaderFileInfo.Path.data());
			std::stringstream stringStream;
			// read file's buffer contents into streams
			stringStream << fileStream.rdbuf();
			// close file handlers
			fileStream.close();
			// convert stream into string
			sourceCode = stringStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::" << shaderTypeName << "::FILE_NOT_SUCCESFULLY_READ - " << shaderFileInfo.Path << std::endl;
		}
		const char* sourceCodePtr = sourceCode.c_str();

		// 2. compile shaders
		const int infoLogLength = 1052;
		uint shaderPtr;
		int success;
		char infoLog[infoLogLength];

		// vertex Shader
		shaderPtr = glCreateShader(shaderFileInfo.Type);
		glShaderSource(shaderPtr, 1, &sourceCodePtr, NULL);
		glCompileShader(shaderPtr);
		// print compile errors if any
		glGetShaderiv(shaderPtr, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderPtr, infoLogLength, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << shaderTypeName << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// shader Program
		if (Id == 0)
		{
			Id = glCreateProgram();
		}
		glAttachShader(Id, shaderPtr);
		glLinkProgram(Id);
		// print linking errors if any
		glGetProgramiv(Id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(Id, infoLogLength, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(shaderPtr);
	}
}

void Shader::Use()
{
	glUseProgram(Id);
}

void Shader::SetBool(const string_view& name, bool value) const
{
	glUniform1i(glGetUniformLocation(Id, name.data()), (int)value);
}

void Shader::SetInt(const string_view& name, int value) const
{
	glUniform1i(glGetUniformLocation(Id, name.data()), value);
}

void Shader::SetFloat(const string_view& name, float value) const
{
	glUniform1f(glGetUniformLocation(Id, name.data()), value);
}

void Shader::SetVec2(const string_view& name, const vec2& value) const
{
	glUniform2fv(glGetUniformLocation(Id, name.data()), 1, &value[0]);
}

void Shader::SetVec2(const string_view& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(Id, name.data()), x, y);
}

void Shader::SetVec3(const string_view& name, const vec3& value) const
{
	glUniform3fv(glGetUniformLocation(Id, name.data()), 1, &value[0]);
}

void Shader::SetVec3(const string_view& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(Id, name.data()), x, y, z);
}

void Shader::SetVec4(const string_view& name, const vec4& value) const
{
	glUniform4fv(glGetUniformLocation(Id, name.data()), 1, &value[0]);
}

void Shader::SetVec4(const string_view& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(Id, name.data()), x, y, z, w);
}

void Shader::SetMat2(const string_view& name, const mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(Id, name.data()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const string_view& name, const mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(Id, name.data()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const string_view& name, const mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(Id, name.data()), 1, GL_FALSE, &mat[0][0]);
}
