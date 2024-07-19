#ifndef SNAKE_PART_H
#define SNAKE_PART_H

#include <string>

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"
#include "Include/glm/gtc/type_ptr.hpp"

namespace snake {
enum class movement { RIGHT, LEFT, UP, DOWN };

class SnakePart {
  using SELF = SnakePart;

  glm::vec3 trans, scale;
  movement direction;

 public:
  SnakePart(glm::vec3 startTrans, float scale_factor, movement startDir);

  SELF& move(float increment, float borderx, float borderz);

  glm::vec3& getTrans();

  movement getDirection() const;
  movement updateDirection(movement newDirection);

  SELF& draw(GLuint shaderID, const std::string& uniformName);
};

};  // namespace snake

#endif
