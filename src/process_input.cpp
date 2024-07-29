#include "process_input.h"

#include <iostream>

#include "SnakePart.h"

extern int window_height;
extern int window_width;

extern snake::movement current;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  window_height = height;
  window_width = width;
}

void processInput(GLFWwindow* window, bool gameOn) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  else if (gameOn) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
      current = snake::movement::LEFT;
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      current = snake::movement::RIGHT;
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
      current = snake::movement::UP;
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
      current = snake::movement::DOWN;
  }
}

GLFWwindow* initializeWindow(const unsigned int width,
                             const unsigned int height, const char* title) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    return NULL;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return NULL;
  }

  glEnable(GL_DEPTH_TEST);

  glViewport(0, 0, width, height);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  return window;
}
