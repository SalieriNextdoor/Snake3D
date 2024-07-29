/**
 * @file shader.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Defines and implements the class for the shaders.
 */
#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"
#include "Include/glm/gtc/type_ptr.hpp"

/**
 * @brief Defines the methods for Shader compilation and behavior.
 */
class Shader {
  using SELF = Shader;

 public:
  GLuint ID;

  /**
   * @brief Constructor for a shader.
   *
   * @param vertexPath path to the vertex GLSL file
   * @param fragmentPath path to the fragment GLSL file
   *
   * The given files are read, compiled and linked into a shader program.
   *
   * Any errors are logged to the console.
   */
  Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      std::stringstream vShaderStream, fShaderStream;
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      vShaderFile.close();
      fShaderFile.close();
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
    } catch (const std::ifstream::failure &e) {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragment, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << std::endl;
    }

    glDetachShader(ID, vertex);
    glDeleteShader(vertex);
    glDetachShader(ID, fragment);
    glDeleteShader(fragment);
  }

  /**
   * @brief Use the shader program.
   *
   * @return reference to the object
   */
  SELF &use() {
    glUseProgram(ID);
    return *this;
  }

  /**
   * @brief Set a bool uniform.
   *
   * @param name uniform name
   * @param value given uniform value
   */
  void setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  }
  /**
   * @brief Set an int uniform.
   *
   * @param name uniform name
   * @param value given uniform value
   */
  void setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
  /**
   * @brief Set a float uniform.
   *
   * @param name uniform name
   * @param value given uniform value
   */
  void setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }
  /**
   * @brief Set a 2D vector uniform.
   *
   * @param name uniform name
   * @param value given uniform value
   */
  void setv2fv(const std::string &name, glm::vec2 vec) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1,
                 glm::value_ptr(vec));
  }
  /**
   * @brief Set a 4D vector uniform.
   *
   * @param name uniform name
   * @param value given uniform value
   */
  void setv4fv(const std::string &name, glm::vec4 vec) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1,
                 glm::value_ptr(vec));
  }
  /**
   * @brief Set a 4D matrix uniform.
   *
   * @param name uniform name
   * @param value given uniform value
   */
  void setm4fv(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       glm::value_ptr(mat));
  }

  /**
   * @brief Destructor for the Shader, deleting the shader program.
   */
  ~Shader() { glDeleteProgram(ID); }
};

#endif
