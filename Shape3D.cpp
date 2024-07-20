#include "Shape3D.h"

using SELF = Shape3D;

Shape3D::Shape3D(GLsizeiptr data_size, const void* data,
                 GLsizeiptr indices_size, const void* indices) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
}

SELF& Shape3D::bind() {
  glBindVertexArray(VAO);
  return *this;
}

Shape3D::~Shape3D() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

