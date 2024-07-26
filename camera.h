#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"

const float YAW = 0.0f;
const float PITCH = 0.0f;

class Camera {
  using SELF = Camera;

  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 worldup;
  float yaw;
  float pitch;

  SELF& updateUp() {
    auto directionRight = glm::normalize(glm::cross(worldup, front));
    up = glm::normalize(glm::cross(front, directionRight));

    return *this;
  }

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

  glm::mat4 lookAt() { return glm::lookAt(position, position + front, up); }

  // move straight; speed > 0 frontward, otherwise backward
  SELF& straight(float speed) {
    position += front * speed;
    return *this;
  }

  // move sideways; speed > 0 right, otherwise left
  SELF& strafe(float speed) {
    auto stp = glm::normalize(glm::cross(front, up));
    position += stp * speed;
    return *this;
  }

  SELF& updateYaw(float offset, bool doUpdate = true) {
    yaw += offset;

    return doUpdate ? updateDirection() : *this;
  }

  SELF& updatePitch(float offset, bool doUpdate = true,
                    bool constrainPitch = true) {
    pitch += offset;

    if (constrainPitch) {
      if (pitch > 89.0f)
        pitch = 89.0f;
      else if (pitch < -89.0f)
        pitch = -89.0f;
    }

    return doUpdate ? updateDirection() : *this;
  }

  void printInfo() {
    std::cout << "Yaw: " << yaw << "\nPitch: " << pitch << std::endl;
  }
};

#endif

