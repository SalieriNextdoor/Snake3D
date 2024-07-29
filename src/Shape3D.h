/**
 * @file Shape3D.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Declares the class for a 3D shape.
 */
#ifndef SHAPE3D_H
#define SHAPE3D_H

#include "Include/glad/glad.h"
/**
 * @brief Defines the methods for the representation of a 3D Shape in space,
 * according to given vertex data.
 */
class Shape3D {
  using SELF = Shape3D;

  GLuint VAO, VBO, EBO;

 public:
  /**
   * @brief Constructor for the 3D shape.
   *
   * @param data_size byte size of the vertex data
   * @param data vertex data as an array of floats
   * @param indices_size byte size of the indice data
   * @param indices data as an array of unsigned integers
   */
  Shape3D(GLsizeiptr data_size, const void* data, GLsizeiptr indices_size,
          const void* indices);

  /**
   * @brief Bind the vertex array.
   *
   * @return reference to the object
   */
  SELF& bind();

  /**
   * @brief Destructor for the 3D Shape, deleting the associated buffers.
   */
  ~Shape3D();
};

#endif
