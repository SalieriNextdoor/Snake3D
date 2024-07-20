#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"

namespace settingConstants {

const float zoom = 45.0f;
const double delay = 0.5f;

};  // namespace settingConstants

namespace modelConstants {

const float vertices_cube[] = {
    // position
    -0.5f, -0.5f, -0.5f,  // 0
    0.5f,  -0.5f, -0.5f,  // 1
    0.5f,  0.5f,  -0.5f,  // 2
    -0.5f, 0.5f,  -0.5f,  // 3

    -0.5f, -0.5f, 0.5f,  // 4
    0.5f,  -0.5f, 0.5f,  // 5
    0.5f,  0.5f,  0.5f,  // 6
    -0.5f, 0.5f,  0.5f,  // 7
};

const float vertices_plane[] = {
    // position
    -1.0f, -1.0f, -1.0f,  // 0
    1.0f,  -1.0f, -1.0f,  // 1
    1.0f,  1.0f,  -1.0f,  // 2
    -1.0f, 1.0f,  -1.0f,  // 3

    -1.0f, -1.0f, -1.1f,  // 4
    1.0f,  -1.0f, -1.1f,  // 5
    1.0f,  1.0f,  -1.1f,  // 6
    -1.0f, 1.0f,  -1.0f,  // 7
};

const GLuint indices_cube[] = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7,
                               0, 3, 7, 0, 4, 7, 2, 6, 1, 1, 5, 6,
                               0, 1, 5, 0, 3, 5, 3, 2, 6, 3, 6, 7};

const glm::vec4 colorSnake = glm::vec4(0.47f, 0.65f, 0.21f, 1.0f);
const glm::vec4 colorPoint = glm::vec4(0.93f, 0.35f, 0.31f, 1.0f);
const glm::vec4 colorPlane = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

const float scale_factor = 0.10f;

};  // namespace modelConstants

#endif
