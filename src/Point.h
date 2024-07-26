#ifndef POINT_H
#define POINT_H

#include <string>

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"
#include "Include/glm/gtc/type_ptr.hpp"

class Point {
  using SELF = Point;

  glm::vec3 trans, scale;

 public:
  Point(glm::vec3 posTrans, float scale_factor);

  glm::vec3& getTrans();

  SELF& draw(GLuint shaderID, const std::string& uniformName);
};

#endif
