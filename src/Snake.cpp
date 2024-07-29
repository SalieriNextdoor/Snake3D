/**
 * @file SnakePart.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Implements the class for the parts of the Snake.
 */
#include "Snake.h"

#include <iostream>

using SELF = snake::Snake;

namespace snake {

constexpr snake::movement invertDirection(const snake::movement dir) {
  switch (dir) {
    case snake::movement::DOWN:
      return snake::movement::UP;
    case snake::movement::UP:
      return snake::movement::DOWN;
    case snake::movement::RIGHT:
      return snake::movement::LEFT;
    case snake::movement::LEFT:
      return snake::movement::RIGHT;
    default:
      return snake::movement::DOWN;  // will never run
  }
}

constexpr bool floatEquality(float a, float b, float e) {
  return (a <= b + e && a >= b - e);
}

Snake::Snake(glm::vec3 startTransHead, int startingSize, float scale_factor,
             float increment_val, float borderx, float borderz,
             movement startDir)
    : scaleFactor{scale_factor},
      increment{increment_val},
      borderx{borderx},
      borderz{borderz},
      generalDirection{startDir} {
  SnakePart *head = new SnakePart(startTransHead, scale_factor, startDir);
  parts.push_back(head);
  for (int i = 1; i < startingSize; i++) addPart();
}

/**
 * A new part is created and added to the back of the Snake's tail, with the
 * same direction and position of the part preceding it. It is then moved once
 * in the opposite direction, as to thus increase the size of the tail.
 */
SELF &Snake::addPart() {
  auto *last = parts.back();
  movement dir = last->getDirection();
  auto trans = last->getTrans();
  SnakePart *part = new SnakePart(trans, scaleFactor, invertDirection(dir));
  part->move(increment, borderx, borderz);
  part->updateDirection(dir);
  parts.push_back(part);

  return *this;
}

/*
 *The head's direction will not be changed in the case where the new direction
 *is the opposite of its initial direction.
 */
SELF &Snake::updateDirection(movement newHeadDir) {
  if (newHeadDir != invertDirection(generalDirection))
    parts[0]->updateDirection(newHeadDir);
  return *this;
}

/**
 * Each part of the Snake is moved according to the increment by a call to each
 * part's move function. Afterwards, each part is updated with the direction of
 * the part in front of it, with the exception of the head.
 */
SELF &Snake::move() {
  parts[0]->move(increment, borderx, borderz);
  movement old = parts[0]->getDirection();
  generalDirection = old;
  for (size_t i = 1; i < parts.size(); i++) {
    parts[i]->move(increment, borderx, borderz);
    old = parts[i]->updateDirection(old);
  }

  return *this;
}

/**
 * A cube shape must be bound and a shader program must be active before this
 * function is called.
 * @see Shape3D
 * @see Shader
 * @see snake::SnakePart::draw
 */
SELF &Snake::draw(GLuint shaderID, const std::string &uniformName) {
  for (auto *part : parts) part->draw(shaderID, uniformName);
  return *this;
}

bool Snake::selfCollision() const {
  glm::vec3 headTrans = parts[0]->getTrans();
  for (size_t i = 1; i < parts.size(); i++) {
    glm::vec3 temp = parts[i]->getTrans();
    if (floatEquality(temp.x, headTrans.x, 0.001f) &&
        floatEquality(temp.z, headTrans.z, 0.001f))
      return true;
  }
  return false;
}

bool Snake::pointCollisionHead(const glm::vec3 &pointTrans) const {
  glm::vec3 headTrans = parts[0]->getTrans();
  return (floatEquality(headTrans.x, pointTrans.x, 0.001f) &&
          floatEquality(headTrans.z, pointTrans.z, 0.001f));
}

bool Snake::pointCollisionAll(const glm::vec3 &pointTrans) const {
  for (auto *part : parts) {
    glm::vec3 trans = part->getTrans();
    if (floatEquality(trans.x, pointTrans.x, 0.001f) &&
        floatEquality(trans.z, pointTrans.z, 0.001f))
      return true;
  }
  return false;
}

/**
 * Deletes all of the previously created SnakePart associated with the Snake.
 */
Snake::~Snake() {
  for (auto *part : parts) delete part;
}
};  // namespace snake
