#include "Shader.h"
#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utilities.h"

ShaderProgramSource Shader::ParseShader()
{
	std::ifstream stream(m_FilePath);

	enum class ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string actLine;
	std::stringstream stringStream[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, actLine))
	{
		if (actLine.find("#shader") != std::string::npos)
		{
			if (actLine.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (actLine.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			stringStream[(int)type] << actLine << "\n";
		}
	}

	return { stringStream[0].str(), stringStream[1].str() };
}

void Shader::CompileShader(unsigned int shaderID, unsigned int type, const std::string& source)
{
	const char* src = source.c_str();
	GLCALL(glShaderSource(shaderID, 1, &src, nullptr));
	GLCALL(glCompileShader(shaderID));

	int result;
	GLCALL(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCALL(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCALL(glGetShaderInfoLog(shaderID, length, &length, message));
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		GLCALL(glDeleteShader(shaderID));
		return;
	}
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();

	GLCALL(unsigned int vs = glCreateShader(GL_VERTEX_SHADER));
	CompileShader(vs, GL_VERTEX_SHADER, vertexShader);

	GLCALL(unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER));
	CompileShader(fs, GL_FRAGMENT_SHADER, fragmentShader);

	GLCALL(glAttachShader(program, vs));
	GLCALL(glAttachShader(program, fs));
	GLCALL(glLinkProgram(program));
	GLCALL(glValidateProgram(program));

	GLCALL(glDetachShader(program, vs));
	GLCALL(glDetachShader(program, fs));

	GLCALL(glDeleteShader(vs));
	GLCALL(glDeleteShader(fs));

	return program;
}


Shader::Shader(const std::string& filePath) : m_FilePath(filePath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader();
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCALL(glDeleteProgram(m_RendererID))
}

void Shader::Bind() const
{
	GLCALL(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCALL(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}
void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLCALL(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}
void Shader::SetUniform2f(const std::string& name, float v0, float v1)
{
	GLCALL(glUniform2f(GetUniformLocation(name), v0, v1));
}
void Shader::SetUniform1f(const std::string& name, float v0)
{
	GLCALL(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetUniform4i(const std::string& name, int v0, int v1, int v2, int v3)
{
	GLCALL(glUniform4i(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform3i(const std::string& name, int v0, int v1, int v2)
{
	GLCALL(glUniform3i(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform2i(const std::string& name, int v0, int v1)
{
	GLCALL(glUniform2i(GetUniformLocation(name), v0, v1));
}

void Shader::SetUniform1i(const std::string& name, int v0)
{
	GLCALL(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::SetUniformMatrix4f(const std::string& name, glm::mat4& matrix)
{
	GLCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}


unsigned int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}

	GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
	{
		std::cout << "Warining: uniform " << name << " doesn't exists!" << std::endl;
	}

	m_UniformLocationCache[name] = location;
	return location;
}
