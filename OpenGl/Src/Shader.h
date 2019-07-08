#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

// Compiling a shader from a external source
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
}; // to return the two Shaders as a struct 

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UnLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	//bool CompileShader();
	unsigned int CompileShader(unsigned int type, const std::string source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string fragmentShader);
	int GetUniformLocation(const std::string& name);
	ShaderProgramSource PassShader(const std::string& filepath);
};