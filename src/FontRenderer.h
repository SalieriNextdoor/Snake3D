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

class FontRenderer {
  using SELF = FontRenderer;
  int numberSequenceStart, letterSequenceStart;
  Shape3D quadFontShape;
  Shader fontShader;

  SELF& shiftTexture(const std::string& uniformName, int xpos, int ypos);

 public:
  GLuint ID;
  GLenum No;
  int width, height;
  int xsize, ysize;

  FontRenderer(const char* texturePath, unsigned int textureNo, GLenum format,
               const Shape3D& _quadFontShape, const Shader& _fontShader,
               const std::string& fontTexUniformName,
               int _xsize = fontConstants::font_char_width,
               int _ysize = fontConstants::font_char_height,
               int number_seq_start = fontConstants::number_seq_start,
               int letter_seq_start = fontConstants::letter_seq_start);
  FontRenderer(const FontRenderer&) = delete;

  SELF& shiftToChar(const char c, const std::string& uniformName);

  SELF& writeText(const std::string& text, float scaleFactor,
                  float startingPosX, float startingPosY, float xgap,
                  float ygap, const std::string& textUniformName,
                  const std::string& modelUniformName);

  SELF& bind();

  SELF& active();
};

#endif
