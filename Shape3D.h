#ifndef SHAPE3D_H
#define SHAPE3D_H

#include "Include/glad/glad.h"

class Shape3D {
  using SELF = Shape3D;

  GLuint VAO, VBO, EBO;

 public:
  Shape3D(GLsizeiptr data_size, const void* data, GLsizeiptr indices_size,
          const void* indices);

  Shape3D(const Shape3D&) = delete;

  SELF& bind();

  ~Shape3D();
};

#endif
