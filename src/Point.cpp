/**
 * @file Point.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Implements the class for the Point.
 */
#include "Point.h"

using SELF = Point;

Point::Point(glm::vec3 posTrans, float scale_factor)
    : trans{posTrans}, scale{scale_factor, scale_factor, scale_factor} {}

glm::vec3& Point::getTrans() { return trans; }

/**
 * A cube shape must be bound and a shader program must be active before this
 * function is called.
 * @see Shape3D
 * @see Shader
 */
SELF& Point::draw(GLuint shaderID, const std::string& uniformName) {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, trans);
  model = glm::scale(model, scale);

  glUniformMatrix4fv(glGetUniformLocation(shaderID, uniformName.c_str()), 1,
                     GL_FALSE, glm::value_ptr(model));

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

  return *this;
}
