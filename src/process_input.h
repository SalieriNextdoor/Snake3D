/**
 * @file process_input.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Declares input and window processing functions.
 */
#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <GLFW/glfw3.h>

#include "camera.h"

/**
 * @brief Processes keyboard input.
 *
 * @param window current session's window
 * @param gameOn whether or not the game is running
 */
void processInput(GLFWwindow* window, bool gameOn = true);

/**
 * @brief Initializes the session window.
 *
 * @param width window width value
 * @param height window height value
 * @param title window title
 *
 * @return pointer to the created window, or null if failed
 */
GLFWwindow* initializeWindow(const unsigned int width,
                             const unsigned int height, const char* title);

#endif
