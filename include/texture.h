#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture {
  public:
    Texture(int numTextures, const std::string fileNames[]);

    void Bind(unsigned int unit, int texture);

    virtual ~Texture();
  protected:
  private:
    //Texture(const Texture& other) {}
    //void operator=(const Texture& other) {}

    GLsizei m_numTextures;
    GLuint* m_textures;
};

#endif // TEXTURE_H
