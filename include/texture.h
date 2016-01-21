/**
 * @file texture.cc
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the declerations of a class to manage OpenGL textures.
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture {
  public:
    /**
     * Constructor for a texture object, to contain be used for all textures
     *    for a program.
     *
     * @param numTextures Number of textures to load.
     * @param fileNames Texture files.
     */
    Texture(int numTextures, const std::string fileNames[]);

    /**
     * Activate a desired texture.
     *
     * @param unit Texture unit to be used.
     * @param texture Texture index.
     */
    void Bind(unsigned int unit, int texture);

    /**
     * Texture desctructor. Unload texture from graphics card via OpenGL.
     */
    ~Texture();
  protected:
  private:
    GLsizei m_numTextures;
    GLuint* m_textures;
};

#endif // TEXTURE_H
