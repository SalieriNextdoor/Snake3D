/**
 * @file gameHandler.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Implements functions related to handling game screens and
 * initialization.
 */
#include "gameHandler.h"

#include <random>
#include <thread>

#include "AudioHandler.h"
#include "process_input.h"

snake::movement current = snake::movement::DOWN;

std::mt19937 rng(time(NULL));
std::uniform_int_distribution<int> gen(0,
                                       (int)(2 / modelConstants::scale_factor -
                                             0.5f));

bool initializeGame(GLFWwindow *window, Shader &shaderProgram,
                    Shape3D &planeShape, Shape3D &snakeShape,
                    Shape3D &pointShape, FontRenderer &font) {
  current = snake::movement::DOWN;
  Score score;
  bool rc;

  glm::mat4 planeModel = glm::mat4(1.0f);
  planeModel = glm::rotate(planeModel, glm::radians(-90.0f),
                           glm::vec3(1.0f, 0.0f, 0.0f));

  snake::Snake snek{glm::vec3(-modelConstants::scale_factor / 2,
                              modelConstants::scale_factor / 2 - 0.995f,
                              -modelConstants::scale_factor / 2),
                    3,
                    modelConstants::scale_factor,
                    modelConstants::scale_factor,
                    0.95f,
                    0.95f,
                    current};
  Point point{glm::vec3(-modelConstants::scale_factor / 2,
                        modelConstants::scale_factor / 2 - 0.995f,
                        -modelConstants::scale_factor / 2),
              modelConstants::scale_factor};

  // avoid a point spawning within the Snake
  while (snek.pointCollisionAll(point.getTrans())) {
    point = Point{glm::vec3(modelConstants::scale_factor * gen(rng) +
                                modelConstants::scale_factor / 2 - 1,
                            modelConstants::scale_factor / 2 - 0.995f,
                            modelConstants::scale_factor * gen(rng) +
                                modelConstants::scale_factor / 2 - 1),
                  modelConstants::scale_factor};
  }

  rc = renderMainScreen(window, snek, point, score, shaderProgram, planeShape,
                        snakeShape, pointShape, font, planeModel);
  if (rc) return renderGameOverScreen(window, font, score);
  return rc;
}

bool renderMainScreen(GLFWwindow *window, snake::Snake &snek, Point &point,
                      Score &score, Shader &shaderProgram, Shape3D &planeShape,
                      Shape3D &snakeShape, Shape3D &pointShape,
                      FontRenderer &font, glm::mat4 planeModel) {
  AudioHandler music, move, food;
  std::thread music_audio(

      [&music](const std::string &path) {
        while (music.playAudio(path, 0.08f));
      },
      audioConstants::game_music_path);
  double lastTime = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.use();
    shaderProgram.setm4fv("model", planeModel);

    shaderProgram.setv4fv("ourColor", modelConstants::colorPlane);
    planeShape.bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    snek.updateDirection(current);

    double currentTime = glfwGetTime();
    if (currentTime - lastTime >= settingConstants::delay) {
      snek.move();

      if (snek.selfCollision()) {
        music.stopAudio();
        music_audio.join();
        return true;
      }

      if (snek.pointCollisionHead(point.getTrans())) {
        score.updateScore();
        snek.addPart();
        std::thread food_audio(

            [&food](const std::string &path) { food.playAudio(path, 0.2f); },
            audioConstants::food_path);
        food_audio.detach();
        while (snek.pointCollisionAll(point.getTrans())) {
          point = Point{glm::vec3(modelConstants::scale_factor * gen(rng) +
                                      modelConstants::scale_factor / 2 - 1,
                                  modelConstants::scale_factor / 2 - 0.995f,
                                  modelConstants::scale_factor * gen(rng) +
                                      modelConstants::scale_factor / 2 - 1),
                        modelConstants::scale_factor};
        }
      } else {
        std::thread move_audio(

            [&move](const std::string &path) { move.playAudio(path, 0.2f); },
            audioConstants::move_path);
        move_audio.detach();
      }

      lastTime = currentTime;
    }

    shaderProgram.setv4fv("ourColor", modelConstants::colorSnake);
    snakeShape.bind();
    snek.draw(shaderProgram.ID, "model");

    shaderProgram.setv4fv("ourColor", modelConstants::colorPoint);
    pointShape.bind();
    point.draw(shaderProgram.ID, "model");

    // drawing score
    font.writeText(score.getScoreStr(), 0.25f, 3.3f, 3.8f, 0.3f, 0.5f, "texPos",
                   "model");

    // check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  music.stopAudio();
  music_audio.join();
  return false;
}

bool renderStartScreen(GLFWwindow *window, FontRenderer &font) {
  double lastTime = glfwGetTime();
  bool blink = true;
  while (!glfwWindowShouldClose(window)) {
    processInput(window, false);
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) return true;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    font.writeText("SNAKE3D", 0.8f, -0.85f, 0.45f, 0.3f, 0.5f, "texPos",
                   "model");

    double currentTime = glfwGetTime();
    if (currentTime - lastTime > 1.0f) {
      blink = !blink;
      lastTime = currentTime;
    }
    if (blink)
      font.writeText("PRESS ENTER TO START", 0.25f, -2.8f, -2.2f, 0.3f, 0.5f,
                     "texPos", "model");

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  return false;
}

bool renderGameOverScreen(GLFWwindow *window, FontRenderer &font,
                          Score &score) {
  AudioHandler gameover;
  std::thread gameover_audio(

      [&gameover](const std::string &path) { gameover.playAudio(path, 0.2f); },
      audioConstants::gameover_path);
  gameover_audio.detach();
  double lastTime = glfwGetTime();
  bool blink = true;
  std::string scoreStr = std::to_string(score.getScore());
  while (!glfwWindowShouldClose(window)) {
    processInput(window, false);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) return true;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    font.writeText("SCORE " + scoreStr, 0.25f, -0.5f - 0.2f * scoreStr.size(),
                   3.5f, 0.3f, 0.5f, "texPos", "model");
    font.writeText("GAME\nOVER", 0.8f, -0.4f, 0.6f, 0.3f, 0.5f, "texPos",
                   "model");

    double currentTime = glfwGetTime();
    if (currentTime - lastTime > 1.0f) {
      blink = !blink;
      lastTime = currentTime;
    }
    if (blink)
      font.writeText("PRESS R TO RESTART", 0.25f, -2.5f, -2.2f, 0.3f, 0.5f,
                     "texPos", "model");

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  return false;
}
