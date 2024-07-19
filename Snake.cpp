#include "Snake.h"

#include <iostream>

using SELF = snake::Snake;

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

namespace snake {

Snake::Snake(glm::vec3 startTransHead, float scale_factor, float increment_val,
             float borderx, float borderz, movement startDir)
    : scaleFactor{scale_factor},
      increment{increment_val},
      borderx{borderx},
      borderz{borderz},
      generalDirection{startDir} {
  SnakePart *head = new SnakePart(startTransHead, scale_factor, startDir);
  parts.push_back(head);
}

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

SELF &Snake::updateDirection(movement newHeadDir) {
  if (newHeadDir != invertDirection(generalDirection))
    parts[0]->updateDirection(newHeadDir);
  return *this;
}

SELF &Snake::move(float e) {
  parts[0]->move(increment, borderx, borderz);
  movement old = parts[0]->getDirection();
  generalDirection = old;
  for (size_t i = 1; i < parts.size(); i++) {
    parts[i]->move(increment, borderx, borderz);
    old = parts[i]->updateDirection(old);
  }

  return *this;
}

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

bool Snake::pointCollision(const glm::vec3 &pointTrans) const {
  glm::vec3 headTrans = parts[0]->getTrans();
  return (floatEquality(headTrans.x, pointTrans.x, 0.001f) &&
          floatEquality(headTrans.z, pointTrans.z, 0.001f));
}

Snake::~Snake() {
  for (auto *part : parts) delete part;
}

};  // namespace snake
