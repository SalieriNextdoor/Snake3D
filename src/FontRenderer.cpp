/**
 * @file FontRenderer.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Implements the class for the font renderer.
 */
#include "FontRenderer.h"

using SELF = FontRenderer;

/**
 * The texture shifts occurs based on the given positions, which are then
 * converted into coordinates according to the character and image dimensions.
 *
 * The coordinates are then passed to the uniform.
 */
SELF& FontRenderer::shiftTexture(const std::string& uniformName, int xpos,
                                 int ypos) {
  glm::vec2 finalPos{(float)xpos * xsize / width,
                     1.0f - (float)(ypos * ysize - 1) / height};
  fontShader.setv2fv(uniformName, finalPos);
  return *this;
}

/**
 * The font bitmap file is loaded and its width and height extracted.
 *
 * In the case the file is invalid, the error is logged to the terminal.
 */
FontRenderer::FontRenderer(const char* fontPath, unsigned int textureNo,
                           GLenum format, const Shape3D& _quadFontShape,
                           const Shader& _fontShader,
                           const std::string& fontTexUniformName, int _xsize,
                           int _ysize, int number_seq_start,
                           int letter_seq_start)
    : numberSequenceStart{number_seq_start},
      letterSequenceStart{letter_seq_start},
      quadFontShape{_quadFontShape},
      fontShader{_fontShader} {
  fontShader.use();
  No = GL_TEXTURE0 + textureNo;
  xsize = _xsize;
  ysize = _ysize;

  quadFontShape.bind();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glGenTextures(1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  int nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(fontPath, &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
  } else {
    std::cout << "Failed to load texture at " << fontPath << std::endl;
  }
  stbi_image_free(data);

  fontShader.setInt(fontTexUniformName, 0);
}

/**
 * The shift occurs based on the given character and the sequence starting
 * position, which are then converted to x and y axis positions.
 *
 * The function only accepts letters and numbers. Given otherwise, an error will
 * be logged to the terminal.
 */
SELF& FontRenderer::shiftToChar(const char c, const std::string& uniformName) {
  int temp_pos;
  if (c >= '0' && c <= '9')
    temp_pos = numberSequenceStart + c - '0';
  else if (c >= 'a' && c <= 'z')
    temp_pos = letterSequenceStart + c - 'a';
  else if (c >= 'A' && c <= 'Z')
    temp_pos = letterSequenceStart + c - 'A';
  else {
    std::cout << "Character \'" << c << "\' is unavailable." << std::endl;
    return *this;
  }
  int posx = temp_pos % (width / xsize);
  int posy = temp_pos / (width / xsize);
  return shiftTexture(uniformName, posx, posy);
}

/**
 * The text is written character by character, with the given gap between
 * characters and lines.
 *
 * A y line gap is given by a new line character in the string, and a space
 * character is handled as an extra gap.
 */
SELF& FontRenderer::writeText(const std::string& text, float scaleFactor,
                              float startingPosX, float startingPosY,
                              float xgap, float ygap,
                              const std::string& textUniformName,
                              const std::string& modelUniformName) {
  glm::mat4 updatePos = glm::mat4(1.0f);
  updatePos = glm::scale(updatePos,
                         glm::vec3(scaleFactor, scaleFactor, scaleFactor));
  updatePos = glm::translate(updatePos,
                             glm::vec3(startingPosX, startingPosY, 0.0f));
  const glm::vec3 gapVec = glm::vec3(xgap, 0.0f, 0.0f);

  active();
  bind();
  fontShader.use();
  quadFontShape.bind();
  for (size_t i = 0; i < text.size(); i++) {
    if (text[i] == '\n')
      return writeText(text.substr(++i), scaleFactor, startingPosX,
                       startingPosY - ygap, xgap, ygap, textUniformName,
                       modelUniformName);
    if (text[i] != ' ') {
      fontShader.setm4fv(modelUniformName, updatePos);
      shiftToChar(text[i], textUniformName);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    updatePos = glm::translate(updatePos, gapVec);
  }
  return *this;
}

SELF& FontRenderer::bind() {
  glBindTexture(GL_TEXTURE_2D, ID);
  return *this;
}

SELF& FontRenderer::active() {
  glActiveTexture(No);
  return *this;
}
