#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "SnakePart.h"

namespace snake {

class Snake {
  using SELF = Snake;
  std::vector<SnakePart *> parts;
  float scaleFactor, increment, borderx, borderz;
  movement generalDirection;

 public:
  Snake(glm::vec3 startTransHead, int startingSize, float scale_factor,
        float increment_val, float borderx, float borderz,
        movement startDir = movement::DOWN);

  SELF &addPart();

  SELF &updateDirection(movement newHeadDir);

  SELF &move();

  SELF &draw(GLuint shaderID, const std::string &uniformName);

  bool selfCollision() const;

  bool pointCollisionHead(const glm::vec3 &pointTrans) const;
  bool pointCollisionAll(const glm::vec3 &pointTrans) const;

  ~Snake();
};

};  // namespace snake

#endif
