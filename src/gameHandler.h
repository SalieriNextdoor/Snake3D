/**
 * @file gameHandler.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Defines functions related to handling game screens and initialization.
 */
#ifndef SCREEN_HANDLER_H
#define SCREEN_HANDLER_H

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

#include <GLFW/glfw3.h>

#include "FontRenderer.h"
#include "Point.h"
#include "Score.h"
#include "Shape3D.h"
#include "Snake.h"
#include "shader.h"

/**
 * @brief Initialize the game.
 *
 * @param window current session's window
 * @param shaderProgram main model shader program
 * @param planeShape plane the other objects stand on
 * @param snakeShape shape for the Snake
 * @param pointShape shape for the Point
 * @param font font's renderer
 *
 * @see Shape3D
 * @see Shader
 * @see FontRenderer
 *
 * @return whether or not a restart command was given
 */
bool initializeGame(GLFWwindow *window, Shader &shaderProgram,
                    Shape3D &planeShape, Shape3D &snakeShape,
                    Shape3D &pointShape, FontRenderer &font);

/**
 * @brief Render the main game screen.
 *
 * @param window current session's window
 * @param snek game Snake
 * @param point game Point
 * @param score game Score
 * @param shaderProgram main model shader program
 * @param planeShape plane the other objects stand on
 * @param snakeShape shape for the Snake
 * @param pointShape shape for the Point
 * @param font font's renderer
 * @param planeModel plane 4D model matrix
 *
 * @return whether or not a restart command was given
 */
bool renderMainScreen(GLFWwindow *window, snake::Snake &snek, Point &point,
                      Score &score, Shader &shaderProgram, Shape3D &planeShape,
                      Shape3D &snakeShape, Shape3D &pointShape,
                      FontRenderer &font, glm::mat4 planeModel);
/**
 * @brief Render the start menu screen.
 *
 * @param window current session's window
 * @param font font's renderer
 *
 * @return whether or not a start game command was given
 */
bool renderStartScreen(GLFWwindow *window, FontRenderer &font);
/**
 * @brief Render the game over screen.
 *
 * @param window current session's window
 * @param font font's renderer
 * @param Score game scor
 *
 * @return whether or not a restart command was given
 */
bool renderGameOverScreen(GLFWwindow *window, FontRenderer &font, Score &score);

#endif
