/**
 * @file constants.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Defines utility constants.
 */
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"

/**
 * @brief Constants related to game setting parameters.
 */
namespace settingConstants {

const int window_width = 800;
const int window_height = 600;
const float AR = (float)window_width / window_height;
const float zoom = 45.0f;
const double delay = 0.5f;

};  // namespace settingConstants

/**
 * @brief Constants related to audio settings.
 */
namespace audioConstants {

const std::string pcm_device = "default";
const std::string game_music_path = "./assets/audio/game_music.wav";
const std::string move_path = "./assets/audio/move.wav";
const std::string food_path = "./assets/audio/food.wav";
const std::string gameover_path = "./assets/audio/gameover.wav";

};  // namespace audioConstants

/**
 * @brief Constants related to the font bitmap file.
 *
 * @see FontRenderer
 */
namespace fontConstants {

const int bitmap_width = 1024;
const int bitmap_height = 512;
const int font_char_width = 80;
const int font_char_height = 80;
const int number_seq_start = 16;
const int letter_seq_start = 33;

};  // namespace fontConstants

/**
 * @brief Constants related to Score.
 *
 * @see Score
 */
namespace scoreConstants {

const int max_score_digits = 3;

};

/**
 * @brief Constants related to 3D model data definition.
 *
 * @see Shape3D
 */
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
    -1.0f, 1.0f,  -1.1f,  // 7
};

const GLuint indices_cube[] = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7,
                               0, 3, 7, 0, 4, 7, 2, 6, 1, 1, 5, 6,
                               0, 1, 5, 0, 3, 5, 3, 2, 6, 3, 6, 7};

const float vertices_quad[] = {
    0.2f,
    0.2f *
        settingConstants::AR,  // multiplying by aspect ratio to make a square
    0.0f,
    (float)fontConstants::font_char_width / fontConstants::bitmap_width,
    1.0f,
    0.2f,
    -0.2f * settingConstants::AR,
    0.0f,
    (float)fontConstants::font_char_width / fontConstants::bitmap_width,
    1 - (float)fontConstants::font_char_height / fontConstants::bitmap_height,
    -0.2f,
    -0.2f * settingConstants::AR,
    0.0f,
    0.0f,
    1 - (float)fontConstants::font_char_height / fontConstants::bitmap_height,
    -0.2f,
    0.2f * settingConstants::AR,
    0.0f,
    0.0f,
    1.0f};

const GLuint indices_quad[] = {
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
};

const glm::vec4 colorSnake = glm::vec4(0.47f, 0.65f, 0.21f, 1.0f);
const glm::vec4 colorPoint = glm::vec4(0.93f, 0.35f, 0.31f, 1.0f);
const glm::vec4 colorPlane = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

const float scale_factor = 0.10f;

};  // namespace modelConstants

#endif
