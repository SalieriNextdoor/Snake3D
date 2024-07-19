#include "SnakePart.h"

using SELF = snake::SnakePart;

namespace snake {

SnakePart::SnakePart(glm::vec3 startTrans, float scale_factor,
                     movement startDir)
    : trans{startTrans},
      scale{glm::vec3(scale_factor, scale_factor, scale_factor)},
      direction{startDir} {}

SELF& SnakePart::move(float increment, float borderx, float borderz) {
  switch (direction) {
    case movement::RIGHT:
      if (trans.z - increment < -borderz - 0.001f)
        trans.z = -trans.z;
      else
        trans = glm::vec3(trans.x, trans.y, trans.z - increment);
      break;
    case movement::LEFT:
      if (trans.z + increment > borderz + 0.001f)
        trans.z = -trans.z;
      else
        trans = glm::vec3(trans.x, trans.y, trans.z + increment);
      break;
    case movement::UP:
      if (trans.x - increment < -borderx - 0.001f)
        trans.x = -trans.x;
      else
        trans = glm::vec3(trans.x - increment, trans.y, trans.z);
      break;
    case movement::DOWN:
      if (trans.x + increment > borderx + 0.001f)
        trans.x = -trans.x;
      else
        trans = glm::vec3(trans.x + increment, trans.y, trans.z);
      break;
  }
  return *this;
}

glm::vec3& SnakePart::getTrans() { return trans; }

movement SnakePart::getDirection() const { return direction; }

movement SnakePart::updateDirection(movement newDirection) {
  movement old = direction;
  direction = newDirection;
  return old;
}

SELF& SnakePart::draw(GLuint shaderID, const std::string& uniformName) {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, trans);
  model = glm::scale(model, scale);

  glUniformMatrix4fv(glGetUniformLocation(shaderID, uniformName.c_str()), 1,
                     GL_FALSE, glm::value_ptr(model));

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

  return *this;
}

};  // namespace snake
