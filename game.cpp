#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <GLFW/glfw3.h>

#include <iostream>
#include <random>

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"
#include "Include/glm/gtc/type_ptr.hpp"
#include "Point.h"
#include "Score.h"
#include "Shape3D.h"
#include "Snake.h"
#include "camera.h"
#include "constants.h"
#include "process_input.h"
#include "shader.h"

int window_width = 800;
int window_height = 600;

snake::movement current = snake::movement::DOWN;

int main() {
  GLFWwindow *window = initializeWindow(window_width, window_height, "Snake3D");
  if (window == NULL) {
    glfwTerminate();
    return 1;
  }

  Camera camera{glm::vec3(1.6f, 0.5f, 1.6f), glm::vec3(0.0f, 1.0f, 0.0f),
                -45.17f, -38.32f};
  Score score;

  Shape3D snakeShape{
      sizeof(modelConstants::vertices_cube), modelConstants::vertices_cube,
      sizeof(modelConstants::indices_cube), modelConstants::indices_cube};
  snakeShape.bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  Shape3D planeShape{
      sizeof(modelConstants::vertices_plane), modelConstants::vertices_plane,
      sizeof(modelConstants::indices_cube), modelConstants::indices_cube};
  planeShape.bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  Shape3D pointShape{
      sizeof(modelConstants::vertices_cube), modelConstants::vertices_cube,
      sizeof(modelConstants::indices_cube), modelConstants::indices_cube};
  pointShape.bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  Shader shaderProgram{"./shaders/snake/shader.vs",
                       "./shaders/snake/shader.fs"};

  shaderProgram.use();
  shaderProgram.setm4fv("view", camera.lookAt());

  glm::mat4 projection;
  projection = glm::perspective(glm::radians(settingConstants::zoom),
                                (float)window_width / (float)window_height,
                                0.1f, 100.0f);
  shaderProgram.setm4fv("projection", projection);

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

  std::mt19937 rng(time(NULL));
  std::uniform_int_distribution<int> gen(
      0, (int)(2 / modelConstants::scale_factor - 0.5f));
  while (snek.pointCollisionAll(point.getTrans())) {
    point = Point{glm::vec3(modelConstants::scale_factor * gen(rng) +
                                modelConstants::scale_factor / 2 - 1,
                            modelConstants::scale_factor / 2 - 0.995f,
                            modelConstants::scale_factor * gen(rng) +
                                modelConstants::scale_factor / 2 - 1),
                  modelConstants::scale_factor};
  }

  double lastTime = 0.0f;
  bool gameOver = false;
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
    if (currentTime - lastTime >= settingConstants::delay && !gameOver) {
      snek.move();

      if (snek.selfCollision()) {
        gameOver = true;
        std::cout << "Game Over" << std::endl;
      }

      if (snek.pointCollisionHead(point.getTrans())) {
        score.updateScore();
        snek.addPart();
        score.printScore();
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

    // check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  snakeShape.~Shape3D();
  planeShape.~Shape3D();
  pointShape.~Shape3D();
  shaderProgram.~Shader();

  glfwTerminate();
  return 0;
}
