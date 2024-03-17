#pragma once
#include "glad/glad.h"

#include <string>

namespace Bess::Gl {
class Shader {
  public:
    Shader() = default;
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    void bind() const;
    void unbind() const;

  private:
    GLuint m_id;

    GLuint compileShader(const std::string &source, GLenum type);
    GLuint createProgram(const std::string &vertexPath,
                         const std::string &fragmentPath);
    std::string readFile(const std::string &path);
};
} // namespace Bess::Gl
