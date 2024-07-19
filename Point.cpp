#include "Point.h"

using SELF = Point;

Point::Point(glm::vec3 posTrans, float scale_factor)
    : trans{posTrans}, scale{scale_factor, scale_factor, scale_factor} {}

glm::vec3& Point::getTrans() { return trans; }

SELF& Point::draw(GLuint shaderID, const std::string& uniformName) {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, trans);
  model = glm::scale(model, scale);

  glUniformMatrix4fv(glGetUniformLocation(shaderID, uniformName.c_str()), 1,
                     GL_FALSE, glm::value_ptr(model));

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

  return *this;
}
