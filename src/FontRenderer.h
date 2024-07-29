/**
 * @file FontRenderer.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Declares the class for font rendering.
 */
#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

#include <iostream>

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/type_ptr.hpp"
#include "Include/stb_image/stb_image.h"
#include "Shape3D.h"
#include "constants.h"
#include "shader.h"

/**
 * @brief Defines the methods for reading a bitmap font and drawing it on
 * screen.
 *
 * @see Shape3D
 * @see Shader
 */
class FontRenderer {
  using SELF = FontRenderer;
  int numberSequenceStart, letterSequenceStart;
  Shape3D quadFontShape;
  Shader fontShader;

  /**
   * @brief Shifts the texture coordinates by an amount of characters in the x
   * and y axes.
   *
   * @param uniformName uniform name for a 2D vector in the shaders for texture
   * @param xpos position of the character in the x axis, starting at 0
   * @param ypos position of the character in the y axis, starting at 0
   *
   * @return reference to the object
   */
  SELF& shiftTexture(const std::string& uniformName, int xpos, int ypos);

 public:
  GLuint ID;
  GLenum No;
  int width, height;
  int xsize, ysize;

  /**
   * @brief Constructor for the font renderer.
   *
   * @param fontPath file path for the bitmap font file
   * @param textureNo given texture number, starting at 0
   * @param format the format of GL color representation, e.g. GL_RGB
   * @param _quadFontShape the Shape3D for a quad, composed of two triangles
   * @param _fontShader the Shader associated with the font
   * @param fontTexUniformName the uniform name for the font texture in the
   * shader
   * @param _xsize the width of each character in the font file
   * @param _ysize the height of each character in the font file
   * @param number_seq_start the position of the first number, starting from 0
   * from the top left and counting rightwards
   * @param letter_seq_start the position of the first letter, starting from 0
   * from the top left and counting rightwards
   *
   * @see Shape3D
   * @see Shader
   */
  FontRenderer(const char* fontPath, unsigned int textureNo, GLenum format,
               const Shape3D& _quadFontShape, const Shader& _fontShader,
               const std::string& fontTexUniformName,
               int _xsize = fontConstants::font_char_width,
               int _ysize = fontConstants::font_char_height,
               int number_seq_start = fontConstants::number_seq_start,
               int letter_seq_start = fontConstants::letter_seq_start);
  FontRenderer(const FontRenderer&) = delete;

  /**
   * @brief Shift the texture coordinates to the given character
   *
   * @param c character to be shifted to
   * @param uniformName uniform name for a 2D vector in the shaders for texture
   * position coordinate addition
   *
   * @return reference to the object
   *
   * @see FontRenderer::shiftTexture
   */
  SELF& shiftToChar(const char c, const std::string& uniformName);

  /**
   * Write text to the screen.
   *
   * @param text string of text to be written
   * @param scaleFactor scaling for the font size
   * @param startingPosX starting position of the first character in the x axis
   * @param startingPosY starting position of the first character in the y axis
   * @param xgap the gap between character in the x axis
   * @param ygap the gap between lines in the y axis
   * @param textUniformName uniform name for a 2D vector in the shaders for
   * texture position coordinate addition
   * @param modelUniformName uniform name for the quad model
   *
   * @return reference to the object
   *
   * @see FontRenderer::shiftToChar
   * @see FontRenderer::shiftTexture
   */
  SELF& writeText(const std::string& text, float scaleFactor,
                  float startingPosX, float startingPosY, float xgap,
                  float ygap, const std::string& textUniformName,
                  const std::string& modelUniformName);

  /**
   * @brief Bind the font texture.
   *
   * @return reference to the object
   */
  SELF& bind();

  /**
   * @brief Activate the font texture.
   *
   * @return reference to the object
   */
  SELF& active();
};

#endif
