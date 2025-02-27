#pragma once
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

#include <string>

class ShaderProgram {
public:
    ShaderProgram() = default;
    ~ShaderProgram();

    bool load(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;
    GLuint getID() const;

private:
    std::string readFile(const std::string& path);
    GLuint compileShader(GLenum type, const std::string& source);
    bool linkProgram(GLuint vs, GLuint fs);

    GLuint m_id = 0;
};
