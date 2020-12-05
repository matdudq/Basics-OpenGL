#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string,int> m_UniformLocationCache;

public:
	Shader(const std::string& filename);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform1f(const std::string& name, float v0);

	void SetUniform4i(const std::string& name, int v0, int v1, int v2, int v3);
	void SetUniform3i(const std::string& name, int v0, int v1, int v2);
	void SetUniform2i(const std::string& name, int v0, int v1);
	void SetUniform1i(const std::string& name, int v0);

	void SetUniformMatrix4f(const std::string& name, glm::mat4& mat4);

private:
	unsigned int GetUniformLocation(const std::string& name);

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	void CompileShader(unsigned int shaderID, unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader();
};

