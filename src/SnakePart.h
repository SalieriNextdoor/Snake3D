/**
 * @file SnakePart.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Declares the class for the parts of the Snake.
 */

#ifndef SNAKE_PART_H
#define SNAKE_PART_H

#include <string>

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"
#include "Include/glm/gtc/type_ptr.hpp"

/**
 * @brief Relates to classes, enums and methods concerning the Snake and its
 * behavior.
 */
namespace snake {

/**
 * @brief Represents the direction of movement of the Snake and its parts.
 */
enum class movement { RIGHT, LEFT, UP, DOWN };

/**
 * @brief Defines the methods for the behavior of each part of the Snake.
 */
class SnakePart {
  using SELF = SnakePart;

  glm::vec3 trans, scale;
  movement direction;

 public:
  /**
   * @brief Constructor for a part of the Snake.
   *
   * @param startTrans the starting position of the part in 3D space
   * @param scale_factor the factor by which the 3D render of the part
   * must be scaled
   * @param startDir the initial direction of movement of the part
   */
  SnakePart(glm::vec3 startTrans, float scale_factor, movement startDir);

  /**
   * @brief Cause the Snake part to move in its current direction over a plane.
   *
   * @param increment The amount by which the part should move
   * @param borderx The x limit of the plane
   * @param borderz The z limit of the plane
   *
   * @return reference to the object
   */
  SELF& move(float increment, float borderx, float borderz);

  /**
   * @brief Get a reference to the part's transform vector.
   *
   * @return reference to the part's transform 3D vector
   */
  glm::vec3& getTrans();

  /**
   * @brief Get the current direction of the Snake part.
   *
   * @return the part's current direction as a movement
   * @see snake::movement
   */
  movement getDirection() const;
  /**
   * @brief Change current direction of the Snake part.
   *
   * @param newDirection the new direction to be applied to the part
   * @return the part's direction from before the change
   * @see snake::movement
   */
  movement updateDirection(movement newDirection);

  /**
   * @brief Draw the Snake part in 3D space according to its vectors.
   *
   * @param shaderID the id of the shader to be used for the part
   * @param uniformName the name of the uniform for the part's model matrix
   * @return reference to the object
   */
  SELF& draw(GLuint shaderID, const std::string& uniformName);
};

};  // namespace snake

#endif
