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

  return renderMainScreen(window, snek, point, score, shaderProgram, planeShape,
                          snakeShape, pointShape, font, planeModel);
}

bool renderMainScreen(GLFWwindow *window, snake::Snake &snek, Point &point,
                      Score &score, Shader &shaderProgram, Shape3D &planeShape,
                      Shape3D &snakeShape, Shape3D &pointShape,
                      FontRenderer &font, glm::mat4 planeModel) {
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

      if (snek.selfCollision())
        return renderGameOverScreen(window, font, score);

      if (snek.pointCollisionHead(point.getTrans())) {
        score.updateScore();
        snek.addPart();
        while (snek.pointCollisionAll(point.getTrans())) {
          point = Point{glm::vec3(modelConstants::scale_factor * gen(rng) +
                                      modelConstants::scale_factor / 2 - 1,
                                  modelConstants::scale_factor / 2 - 0.995f,
                                  modelConstants::scale_factor * gen(rng) +
                                      modelConstants::scale_factor / 2 - 1),
                        modelConstants::scale_factor};
        }
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
