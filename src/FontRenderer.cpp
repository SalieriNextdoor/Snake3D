#include "FontRenderer.h"

using SELF = FontRenderer;

SELF& FontRenderer::shiftTexture(GLuint shaderID, std::string uniformName,
                                 int xpos, int ypos) {
  glm::vec2 finalPos{(float)xpos * xsize / width,
                     1.0f - (float)ypos * ysize / height};
  glUniform2fv(glGetUniformLocation(shaderID, uniformName.c_str()), 1,
               glm::value_ptr(finalPos));
  return *this;
}

FontRenderer::FontRenderer(const char* texturePath, unsigned int textureNo,
                           GLenum format, int _xsize, int _ysize) {
  No = GL_TEXTURE0 + textureNo;
  xsize = _xsize;
  ysize = _ysize;

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
}

SELF& FontRenderer::shiftToChar(const char c, int sequence_start,
                                GLuint shaderID, std::string uniformName) {
  int temp_pos = sequence_start;
  if (c >= '0' && c <= '9')
    temp_pos += c - '0';
  else if (c >= 'a' && c <= 'z')
    temp_pos += c - 'a';
  else if (c >= 'A' && c <= 'Z')
    temp_pos += c - 'A';
  else {
    std::cout << "Character \'" << c << "\' is unavailable." << std::endl;
    return *this;
  }
  int posx = temp_pos % (width / xsize);
  int posy = temp_pos / (width / xsize);
  return shiftTexture(shaderID, uniformName, posx, posy);
}

SELF& FontRenderer::bind() {
  glBindTexture(GL_TEXTURE_2D, ID);
  return *this;
}

SELF& FontRenderer::active() {
  glActiveTexture(No);
  return *this;
}
