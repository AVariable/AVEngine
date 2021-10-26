#include "Shader.h"

#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Renderer.h"

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

Shader::Shader(const std::string& filepath) :
	_filepath(filepath),
	_rendererId(0) {
    ShaderProgramSource source = ParseShader(filepath);
    _rendererId = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(_rendererId));
}

void Shader::Bind() const {
    GLCall(glUseProgram(_rendererId));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value) {
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float value0, float value1, float value2, float value3) {
    GLCall(glUniform4f(GetUniformLocation(name), value0, value1, value2, value3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) {
    if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
        return _uniformLocationCache.at(name);

    GLCall(int location = glGetUniformLocation(_rendererId, name.c_str()));
    if (location == -1) {
        printf("Warning: uniform '%s' does not exist!\n", name.c_str());
    }
    _uniformLocationCache[name] = location;
    return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath) {
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        } else {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned Shader::CompileShader(unsigned type, const std::string& source) {
    unsigned id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        std::string message;
        message.resize(length);
        glGetShaderInfoLog(id, length, &length, (char*)message.c_str());
        printf("Failed to compile %s shader!\n", type == GL_VERTEX_SHADER ? "vertex" : "fragment");
        printf("%s\n", message.c_str());
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned program = glCreateProgram();
    unsigned vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
