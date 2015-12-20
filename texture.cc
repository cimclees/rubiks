#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName) {
  
  // Load texture from file using stb_image library
  int width, height, numComponents;
  unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, 
                                       &numComponents, 4);
  if (imageData == NULL) {
    std::cerr << "Texture loading failed for texture: " << fileName 
              << std::endl;
  }

  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);


  // Texture wrap setting
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // Texture magnification setting
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Send texture to GPU (load in GL)
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, 
               GL_UNSIGNED_BYTE, imageData);

  // Free texture from main memory
  stbi_image_free(imageData);
}
    
void Texture::Bind(unsigned int unit) {
  assert(unit >= 0 && unit <= 31);

  // Choose active texture
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, m_texture);
}

Texture::~Texture() {
  // Delete texture from GPU memory
  glDeleteTextures(1, &m_texture);
}
