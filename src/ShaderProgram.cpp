#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <vector>

ShaderProgram::~ShaderProgram() {
    if (m_id != 0) {
        glDeleteProgram(m_id);
    }
}

bool ShaderProgram::load(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vsSource = readFile(vertexPath);
    std::string fsSource = readFile(fragmentPath);

    if (vsSource.empty() || fsSource.empty()) {
        std::cerr << "Failed to read shader files." << std::endl;
        return false;
    }

    GLuint vs = compileShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSource);

    bool success = linkProgram(vs, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return success;
}

void ShaderProgram::use() const {
    glUseProgram(m_id);
}

GLuint ShaderProgram::getID() const {
    return m_id;
}

std::string ShaderProgram::readFile(const std::string& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file) return {};
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    if (size == 0) return {};
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size + 1);
    file.read(buffer.data(), size);
    buffer[size] = '\0';
    return std::string(buffer.data());
}

GLuint ShaderProgram::compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* srcPtr = source.c_str();
    glShaderSource(shader, 1, &srcPtr, nullptr);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logSize = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<GLchar> infoLog(logSize);
        glGetShaderInfoLog(shader, logSize, nullptr, infoLog.data());
        std::cerr << "Shader compile error: " << infoLog.data() << std::endl;
    }
    return shader;
}

bool ShaderProgram::linkProgram(GLuint vs, GLuint fs) {
    m_id = glCreateProgram();
    glAttachShader(m_id, vs);
    glAttachShader(m_id, fs);
    glLinkProgram(m_id);

    GLint success = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logSize = 0;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<GLchar> infoLog(logSize);
        glGetProgramInfoLog(m_id, logSize, nullptr, infoLog.data());
        std::cerr << "Program link error: " << infoLog.data() << std::endl;
        return false;
    }
    return true;
}
