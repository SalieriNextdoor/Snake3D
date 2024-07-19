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
  Snake(glm::vec3 startTransHead, float scale_factor, float increment_val,
        float borderx, float borderz, movement startDir = movement::DOWN);

  SELF &addPart();

  SELF &updateDirection(movement newHeadDir);

  SELF &move(float e = 0.01f);

  SELF &draw(GLuint shaderID, const std::string &uniformName);

  bool selfCollision() const;

  bool pointCollision(const glm::vec3 &pointTrans) const;

  ~Snake();
};

};  // namespace snake

#endif
