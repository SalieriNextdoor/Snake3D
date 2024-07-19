#include "process_input.h"

#include <iostream>

#include "SnakePart.h"

extern Camera camera;
extern float deltaTime;

extern float speed;
extern float mouse_sensitivity;
extern float zoom;

extern int window_height;
extern int window_width;

extern snake::movement current;

float lastX = window_width / 2.0f, lastY = window_height / 2.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  window_height = height;
  window_width = width;
}

#ifdef DEBUG_MODE
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  zoom -= (float)yoffset * deltaTime * 60.0f;
  if (zoom < 1.0f)
    zoom = 1.0f;
  else if (zoom > 45.0f)
    zoom = 45.0f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  static bool firstMouse = true;
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos;  // reversed since y-coordinates range from bottom to top
  lastX = xpos;
  lastY = ypos;

  camera.updateYaw(xoffset * mouse_sensitivity * deltaTime, false);
  camera.updatePitch(yoffset * mouse_sensitivity * deltaTime);
}
#endif

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

#ifdef DEBUG_MODE
  float velocity = speed * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.straight(velocity);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.straight(-velocity);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.strafe(velocity);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.strafe(-velocity);
  if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) camera.printInfo();
#endif

  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    current = snake::movement::LEFT;
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    current = snake::movement::RIGHT;
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    current = snake::movement::UP;
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    current = snake::movement::DOWN;
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

  glViewport(0, 0, width, height);

  glEnable(GL_DEPTH_TEST);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#ifdef DEBUG_MODE
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif

  return window;
}
