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
#include "Snake.h"
#include "camera.h"
#include "process_input.h"
#include "shader.h"

int window_width = 800;
int window_height = 600;

float speed = 2.5f;
float mouse_sensitivity = 6.0f;
float zoom = 45.0f;

const double delay = 0.5f;
double lastTime = 0.0f;

Camera camera{glm::vec3(1.6f, 0.5f, 1.6f), glm::vec3(0.0f, 1.0f, 0.0f), -45.17f,
              -38.32f};
Score score;

float deltaTime = 0.0f;
double lastFrame = 0.0f;

bool gameOver = false;

snake::movement current = snake::movement::DOWN;

int main() {
  GLFWwindow *window = initializeWindow(window_width, window_height, "Snake3D");
  if (window == NULL) {
    glfwTerminate();
    return 1;
  }

  Shader shaderProgram{"./shaders/snake/shader.vs",
                       "./shaders/snake/shader.fs"};

  const float vertices_part[] = {
      // position             // color
      -0.5f, -0.5f, -0.5f, 0.47f, 0.65f, 0.21f,  // 0
      0.5f,  -0.5f, -0.5f, 0.47f, 0.65f, 0.21f,  // 1
      0.5f,  0.5f,  -0.5f, 0.47f, 0.65f, 0.21f,  // 2
      -0.5f, 0.5f,  -0.5f, 0.47f, 0.65f, 0.21f,  // 3

      -0.5f, -0.5f, 0.5f,  0.47f, 0.65f, 0.21f,  // 4
      0.5f,  -0.5f, 0.5f,  0.47f, 0.65f, 0.21f,  // 5
      0.5f,  0.5f,  0.5f,  0.47f, 0.65f, 0.21f,  // 6
      -0.5f, 0.5f,  0.5f,  0.47f, 0.65f, 0.21f,  // 7
  };

  const GLuint indices_part[] = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7,
                                 0, 3, 7, 0, 4, 7, 2, 6, 1, 1, 5, 6,
                                 0, 1, 5, 0, 3, 5, 3, 2, 6, 3, 6, 7};

  const float vertices_point[] = {
      // position             // color
      -0.5f, -0.5f, -0.5f, 0.93f, 0.35f, 0.31f,  // 0
      0.5f,  -0.5f, -0.5f, 0.93f, 0.35f, 0.31f,  // 1
      0.5f,  0.5f,  -0.5f, 0.93f, 0.35f, 0.31f,  // 2
      -0.5f, 0.5f,  -0.5f, 0.93f, 0.35f, 0.31f,  // 3

      -0.5f, -0.5f, 0.5f,  0.93f, 0.35f, 0.31f,  // 4
      0.5f,  -0.5f, 0.5f,  0.93f, 0.35f, 0.31f,  // 5
      0.5f,  0.5f,  0.5f,  0.93f, 0.35f, 0.31f,  // 6
      -0.5f, 0.5f,  0.5f,  0.93f, 0.35f, 0.31f,  // 7
  };

  float vertices_plane[] = {-1.0f, -1.0f, -1.0f, 0.50f, 0.50f, 0.50f,
                            1.0f,  -1.0f, -1.0f, 0.50f, 0.50f, 0.50f,
                            1.0f,  1.0f,  -1.0f, 0.50f, 0.50f, 0.50f,
                            -1.0f, 1.0f,  -1.0f, 0.50f, 0.50f, 0.50f};

  GLuint indices_plane[] = {0, 1, 2, 0, 2, 3};

  GLuint VAO[3], VBO[3], EBO[3];
  glGenVertexArrays(3, VAO);
  glGenBuffers(3, VBO);
  glGenBuffers(3, EBO);

  glBindVertexArray(VAO[0]);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_part), vertices_part,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_part), indices_part,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(VAO[1]);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_plane), vertices_plane,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_plane), indices_plane,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(VAO[2]);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_point), vertices_point,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_part), indices_part,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  float possible_pos[] = {-0.95f, -0.85f, -0.75f, -0.65f, -0.55f,
                          -0.45f, -0.35f, -0.25f, -0.15f, -0.05f,
                          0.05f,  0.15f,  0.25f,  0.35f,  0.45f,
                          0.55f,  0.65f,  0.75f,  0.85f,  0.95f};
  std::mt19937 rng(time(NULL));
  std::uniform_int_distribution<int> gen(
      0, (int)sizeof(possible_pos) / sizeof(float));

  const float scale_factor = 0.10f;
  Point point{glm::vec3(possible_pos[gen(rng)], scale_factor / 2 - 0.995f,
                        possible_pos[gen(rng)]),
              scale_factor};
  snake::Snake snek{glm::vec3(-scale_factor / 2, scale_factor / 2 - 0.995f,
                              -scale_factor / 2),
                    scale_factor,
                    scale_factor,
                    0.95f,
                    0.95f,
                    current};
  snek.addPart();
  snek.addPart();
  while (!glfwWindowShouldClose(window)) {
    // input
    processInput(window);

    // rendering
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    shaderProgram.use();
    shaderProgram.set4fv("view", camera.lookAt());

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(zoom),
                                  (float)window_width / (float)window_height,
                                  0.1f, 100.0f);
    shaderProgram.set4fv("projection", projection);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-90.0f),
                        glm::vec3(1.0f, 0.0f, 0.0f));
    shaderProgram.set4fv("model", model);

    glBindVertexArray(VAO[1]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    snek.updateDirection(current);

    currentFrame = glfwGetTime();
    if (currentFrame - lastTime >= delay && !gameOver) {
      snek.move();
      if (snek.selfCollision()) {
        gameOver = true;
        std::cout << "Game Over" << std::endl;
      }
      if (snek.pointCollision(point.getTrans())) {
        score.updateScore();
        score.printScore();
        point = Point{
            glm::vec3(possible_pos[gen(rng)], scale_factor / 2 - 0.995f,
                      possible_pos[gen(rng)]),
            scale_factor};
        snek.addPart();
      }
      lastTime = currentFrame;
    }

    glBindVertexArray(VAO[0]);
    snek.draw(shaderProgram.ID, "model");
    glBindVertexArray(VAO[2]);
    point.draw(shaderProgram.ID, "model");

    // check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(3, VAO);
  glDeleteBuffers(3, VBO);
  glDeleteBuffers(3, EBO);
  shaderProgram.~Shader();

  glfwTerminate();
  return 0;
}
