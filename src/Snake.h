/**
 * @file Snake.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Declares the class for the Snake.
 */
#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "SnakePart.h"

namespace snake {

/**
 * @brief Defines the methods for the behavior of the whole Snake, composed of
 * its parts.
 *
 * @see snake::SnakePart
 */
class Snake {
  using SELF = Snake;
  std::vector<SnakePart *> parts;
  float scaleFactor, increment, borderx, borderz;
  movement generalDirection;

 public:
  /**
   * @brief Constructor for the whole Snake.
   *
   * @param startTransHead the starting position of the snake in 3D space,
   * represented as a 3D vector
   * @param startingSize the amount of parts the Snake should be composed of
   * initially
   * @param scale_factor the factor by which the 3D render of each part should
   * be scaled
   * @param increment_val the value by which the Snake will move each time
   * @param borderx the limit of the plane the snake stands on in the x axis
   * @param borderz the limit of the plane the snake stands on in the z axis
   * @param startDir the initial direction of movement of the Snake
   * @see snake::SnakePart
   */
  Snake(glm::vec3 startTransHead, int startingSize, float scale_factor,
        float increment_val, float borderx, float borderz,
        movement startDir = movement::DOWN);

  /**
   * @brief Add a SnakePart to the end of the Snake's tail.
   *
   * @return reference to the object
   */
  SELF &addPart();
  /**
   * @brief Change current direction of the Snake's head.
   *
   * @param newDirection the new direction to be applied to the head
   * @return reference to the object
   * @see snake::movement
   */
  SELF &updateDirection(movement newHeadDir);
  /**
   * @brief Move each part of the Snake according to its direction, and update
   * the direction for each part.
   *
   * @return reference to the object
   * @see snake::SnakePart::move
   */
  SELF &move();
  /**
   * @brief Draw the Snake in 3D space according to each of its parts' vectors.
   *
   * @param shaderID the id of the shader to be used for the models
   * @param uniformName the name of the uniform for the model matrix
   * @return reference to the object
   */
  SELF &draw(GLuint shaderID, const std::string &uniformName);

  /**
   * @brief Check if the Snake's head is occupying the same space as any of its
   * parts.
   *
   * @return true if it is the case, otherwise false
   */
  bool selfCollision() const;

  /**
   * @brief Check if the Snake's head is touching a Point.
   *
   * @param pointTrans 3D vector of the Point's position in space
   * @return true if it is the case, otherwise false
   * @see Point
   */
  bool pointCollisionHead(const glm::vec3 &pointTrans) const;
  /**
   * @brief Check if any of the Snake's parts are touching a Point.
   *
   * @param pointTrans 3D vector of the Point's position in space
   * @return true if it is the case, otherwise false
   * @see Point
   */
  bool pointCollisionAll(const glm::vec3 &pointTrans) const;

  /**
   * @brief Destructor of the whole Snake.
   */
  ~Snake();
};

/**
 * @brief Invert the direction of movement.
 *
 * @param dir the direction of movement
 *
 * @return the inverse of the given direction
 * @see snake::movement
 */
constexpr snake::movement invertDirection(const snake::movement dir);

/**
 * @brief Check the equality of two floats within an epsilon tolerance value.
 *
 * @param a the first value to compare
 * @param b the second value to compare
 * @param e the epsilon value, used as the tolerance value for equality
 *
 * @return the logical result of the equality within the tolerance value
 */
constexpr bool floatEquality(float a, float b, float e);
};  // namespace snake

#endif
