/**
 * @file camera.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Defines and implements the class for the camera.
 */
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"

const float YAW = 0.0f;
const float PITCH = 0.0f;

/**
 * @brief Defines the methods for camera behavior.
 */
class Camera {
  using SELF = Camera;

  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 worldup;
  float yaw;
  float pitch;

  /**
   * @brief Updates the Camera up vector.
   *
   * @return reference to the object
   */
  SELF& updateUp() {
    auto directionRight = glm::normalize(glm::cross(worldup, front));
    up = glm::normalize(glm::cross(front, directionRight));

    return *this;
  }

  /**
   * @brief Updates the Camera's direction vector, according to its rotation
   * values.
   *
   * @return reference to the object
   */
  SELF& updateDirection() {
    glm::vec3 frontv;
    float cospitch = (float)cos(glm::radians(pitch));
    frontv.x = sin(glm::radians(yaw)) * cospitch;
    frontv.y = sin(glm::radians(pitch));
    frontv.z = -cos(glm::radians(yaw)) * cospitch;
    front = glm::normalize(frontv);

    return updateUp();
  }

 public:
  /**
   * @brief Constructor for the Camera.
   *
   * @param position starting position 3D vector
   * @param up starting up 3D vector
   * @param yaw starting yaw rotation value
   * @param pitch starting pitch rotation value
   */
  Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
         const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH)
      : position{position},
        front{glm::vec3(0.0f, 0.0f, -1.0f)},
        worldup{up},
        yaw{yaw},
        pitch{pitch} {
    updateDirection();
  }

  /**
   * @brief Returns the Camera's view matrix.
   *
   * @return view matrix
   */
  glm::mat4 lookAt() { return glm::lookAt(position, position + front, up); }
};

#endif

