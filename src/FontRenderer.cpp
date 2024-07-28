#include "FontRenderer.h"

using SELF = FontRenderer;

SELF& FontRenderer::shiftTexture(const std::string& uniformName, int xpos,
                                 int ypos) {
  glm::vec2 finalPos{(float)xpos * xsize / width,
                     1.0f - (float)(ypos * ysize - 1) / height};
  fontShader.setv2fv(uniformName, finalPos);
  return *this;
}

FontRenderer::FontRenderer(const char* texturePath, unsigned int textureNo,
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
  unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
  } else {
    std::cout << "Failed to load texture at " << texturePath << std::endl;
  }
  stbi_image_free(data);

  fontShader.setInt(fontTexUniformName, 0);
}

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
