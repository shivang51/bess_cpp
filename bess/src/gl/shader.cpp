#include "gl/shader.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

namespace Bess::Gl {
Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    m_id = createProgram(vertexPath, fragmentPath);
}

Shader::~Shader() { glDeleteProgram(m_id); }

void Shader::bind() const { glUseProgram(m_id); }

void Shader::unbind() const { glUseProgram(0); }

GLuint Shader::createProgram(const std::string &vertexPath,
                             const std::string &fragmentPath) {

    auto vertexShader = readFile(vertexPath);
    auto fragmentShader = readFile(fragmentPath);

    auto vertexShaderId = compileShader(vertexShader.c_str(), GL_VERTEX_SHADER);
    auto fragmentShaderId =
        compileShader(fragmentShader.c_str(), GL_FRAGMENT_SHADER);

    auto shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return shaderProgram;
}

std::string Shader::readFile(const std::string &path) {
    std::string content;
    std::ifstream fileStream(path, std::ios::ate);
    if (fileStream.is_open()) {
        size_t fileSize = fileStream.tellg();
        content.resize(fileSize);
        fileStream.seekg(0);
        fileStream.read((char *)content.data(), fileSize);
        fileStream.close();
    } else {
        std::cerr << "Could not read file " << path << std::endl;
    }
    return content;
}

GLuint Shader::compileShader(const std::string &shaderSrc, GLenum shaderType) {
    auto shaderId = glCreateShader(shaderType);
    const char *src = shaderSrc.c_str();
    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    return shaderId;
}

void Shader::setUniformVec4(const std::string &name, const glm::vec4 &value) {
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1,
                 glm::value_ptr(value));
}

void Shader::setUniformMat4(const std::string &name, const glm::mat4 &value) {
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(value));
}

} // namespace Bess::Gl
