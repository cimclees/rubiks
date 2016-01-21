/**
 * @file texture.cc
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the implementation of a class to manage OpenGL textures.
 */

#include <cassert>
#include <iostream>
#include "../include/texture.h"
#include "../lib/stb_image.h"

Texture::Texture(int numTextures, const std::string fileNames[]) {
  
  m_numTextures = numTextures;
  m_textures = new GLuint[m_numTextures];

  glGenTextures(numTextures, m_textures);
  
  for (int i = 0; i < m_numTextures; i++) {
    // Load texture from file using stb_image library
    int width, height, numComponents;
    unsigned char* imageData = stbi_load(fileNames[i].c_str(), &width, &height, 
                                         &numComponents, 4);
    if (imageData == NULL) {
      std::cerr << "Texture loading failed for texture: " << fileNames[i]
                << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, m_textures[i]);

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
}
    
void Texture::Bind(unsigned int unit, int texture) {
  assert(unit >= 0 && unit <= 31);
  assert(texture >= 0 && texture < m_numTextures);

  // Choose active texture
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, m_textures[texture]);
}

Texture::~Texture() {
  // Delete texture from GPU memory
  glDeleteTextures(m_numTextures, m_textures);
  delete [] m_textures;
}
