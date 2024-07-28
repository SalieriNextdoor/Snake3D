#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <GLFW/glfw3.h>

#include "camera.h"

bool processInput(GLFWwindow* window);
GLFWwindow* initializeWindow(const unsigned int width,
                             const unsigned int height, const char* title);

#endif
