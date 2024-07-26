#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

#include <iostream>

#include "Include/glad/glad.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/type_ptr.hpp"
#include "Include/stb_image/stb_image.h"

class FontRenderer {
  using SELF = FontRenderer;

  SELF& shiftTexture(GLuint shaderID, std::string uniformName, int xpos,
                     int ypos);

 public:
  GLuint ID;
  GLenum No;
  int width, height;
  int xsize, ysize;

  FontRenderer(const char* texturePath, unsigned int textureNo, GLenum format,
               int _xsize, int _ysize);
  FontRenderer(const FontRenderer&) = delete;

  SELF& shiftToChar(const char c, int sequence_start, GLuint shaderID,
                    std::string uniformName);

  SELF& bind();

  SELF& active();
};

#endif
