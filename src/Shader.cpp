#include "Shader.h"

#include <iostream>

#include "cmrc/cmrc.hpp"

CMRC_DECLARE(res);

void Shader::init() { program = glCreateProgram(); }

void Shader::load(GLenum shaderType, const char* filename) {
  GLuint shader = glCreateShader(shaderType);

  // Load the file from CMRC
  auto fs = cmrc::res::get_filesystem();
  auto shaderFile = fs.open(filename);

  // Read the contents of the file
  auto shaderSource = std::string(shaderFile.begin(), shaderFile.end()) + "\n";

  // Compile the Shader
  std::cout << "Compiling " << filename << std::endl;
  const char* c_str = shaderSource.c_str();
  glShaderSource(shader, 1, &c_str, nullptr);
  glCompileShader(shader);

  // Check the shader
  GLint result = GL_FALSE;
  int infoLogLength;

  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    char* errorMessage = (char*)malloc(infoLogLength + 1);
    glGetShaderInfoLog(shader, infoLogLength, nullptr, errorMessage);
    std::cerr << errorMessage;
    std::cout << "Compiling failed" << std::endl;
    return;
  }
  std::cout << "Compiling successful" << std::endl;

  glAttachShader(program, shader);
}

void Shader::link() {
  std::cout << "Linking program" << std::endl;
  glLinkProgram(program);

  // Check the program
  GLint result = GL_FALSE;
  int infoLogLength;

  glGetProgramiv(program, GL_LINK_STATUS, &result);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    char* errorMessage = (char*)malloc(infoLogLength + 1);
    glGetProgramInfoLog(program, infoLogLength, nullptr, errorMessage);
    std::cerr << errorMessage;
    return;
  }
  std::cout << "Linking successful" << std::endl;
}

void Shader::attach() { glUseProgram(program); }

void Shader::detach() { glUseProgram(0); }

void Shader::destroy() { glDeleteProgram(program); }

GLint Shader::getUniformLocation(const char* name) { return glGetUniformLocation(program, name); }

void Shader::setUniform(const char* name, GLfloat v0) {
  GLint location = getUniformLocation(name);
  glUniform1f(location, v0);
}

void Shader::setUniform(const char* name, GLfloat v0, GLfloat v1) {
  GLint location = getUniformLocation(name);
  glUniform2f(location, v0, v1);
}

void Shader::setUniform(const char* name, GLfloat v0, GLfloat v1, GLfloat v2) {
  GLint location = getUniformLocation(name);
  glUniform3f(location, v0, v1, v2);
}

void Shader::setUniform(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
  GLint location = getUniformLocation(name);
  glUniform4f(location, v0, v1, v2, v3);
}
