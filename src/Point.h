/**
 * @file Point.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Declares the class for the Point.
 */
#ifndef POINT_H
#define POINT_H

#include <string>

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"
#include "Include/glm/gtc/type_ptr.hpp"
/**
 * @brief Defines the methods for the representation of the Point, which is to
 * be caught by the Snake to drive up Score.
 *
 * @see snake::Snake::pointCollisionHead
 * @see snake::Snake::pointCollisionAll
 * @see Score
 */
class Point {
  using SELF = Point;

  glm::vec3 trans, scale;

 public:
  /**
   * @brief Constructor for the Point.
   *
   * @param posTrans the position of the Point in space according to a 3D vector
   * @param scale_factor a factor for scaling of the Point's 3D representation
   */
  Point(glm::vec3 posTrans, float scale_factor);

  /**
   * @brief Get a reference to the Point's transform vector.
   *
   * @return reference to the Point's transform 3D vector
   */
  glm::vec3& getTrans();

  /**
   * @brief Draw the Point in 3D space according to each of its vector.
   *
   * @param shaderID the id of the shader to be used for the model
   * @param uniformName the name of the uniform for the model matrix
   * @return reference to the object
   */
  SELF& draw(GLuint shaderID, const std::string& uniformName);
};

#endif
