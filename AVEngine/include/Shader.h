#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource;

class Shader {
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float value0, float value1, float value2, float value3);

private:
	std::string _filepath;
	unsigned _rendererId;
	std::unordered_map<std::string, int> _uniformLocationCache;

	ShaderProgramSource Shader::ParseShader(const std::string& filePath);
	unsigned CompileShader(unsigned type, const std::string& source);
	unsigned CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);

	// Caching for uniforms
};
