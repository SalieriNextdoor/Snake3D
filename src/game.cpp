#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <GLFW/glfw3.h>

#include "FontRenderer.h"
#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"
#include "Shape3D.h"
#include "camera.h"
#include "constants.h"
#include "gameHandler.h"
#include "process_input.h"
#include "shader.h"

int window_width = settingConstants::window_width;
int window_height = settingConstants::window_height;

int main() {
  GLFWwindow *window = initializeWindow(window_width, window_height, "Snake3D");
  if (window == NULL) {
    glfwTerminate();
    return 1;
  }

  {
    Camera camera{glm::vec3(1.6f, 0.5f, 1.6f), glm::vec3(0.0f, 1.0f, 0.0f),
                  -45.17f, -38.32f};

    Shape3D snakeShape{
        sizeof(modelConstants::vertices_cube), modelConstants::vertices_cube,
        sizeof(modelConstants::indices_cube), modelConstants::indices_cube};
    snakeShape.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    Shape3D planeShape{
        sizeof(modelConstants::vertices_plane), modelConstants::vertices_plane,
        sizeof(modelConstants::indices_cube), modelConstants::indices_cube};
    planeShape.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    Shape3D pointShape{
        sizeof(modelConstants::vertices_cube), modelConstants::vertices_cube,
        sizeof(modelConstants::indices_cube), modelConstants::indices_cube};
    pointShape.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    Shape3D quadFontShape{
        sizeof(modelConstants::vertices_quad), modelConstants::vertices_quad,
        sizeof(modelConstants::indices_quad), modelConstants::indices_quad};

    Shader shaderProgram{"./shaders/snake/shader.vs",
                         "./shaders/snake/shader.fs"};
    Shader fontShader{"./shaders/font/shader.vs", "./shaders/font/shader.fs"};

    shaderProgram.use();
    shaderProgram.setm4fv("view", camera.lookAt());
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(settingConstants::zoom),
                                  (float)window_width / (float)window_height,
                                  0.1f, 100.0f);
    shaderProgram.setm4fv("projection", projection);

    FontRenderer font{"./images/font.bmp", 0,          GL_RGB,
                      quadFontShape,       fontShader, "texture1"};

    while (initializeGame(window, shaderProgram, planeShape, snakeShape,
                          pointShape, font));
  }

  glfwTerminate();
  return 0;
}
