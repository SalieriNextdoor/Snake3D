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

bool initializeGame(GLFWwindow *window, Shader &shaderProgram,
                    Shape3D &planeShape, Shape3D &snakeShape,
                    Shape3D &pointShape, FontRenderer &font);
bool renderMainScreen(GLFWwindow *window, snake::Snake &snek, Point &point,
                      Score &score, Shader &shaderProgram, Shape3D &planeShape,
                      Shape3D &snakeShape, Shape3D &pointShape,
                      FontRenderer &font, glm::mat4 planeModel);
bool renderGameOverScreen(GLFWwindow *window, FontRenderer &font, Score &score);

#endif
