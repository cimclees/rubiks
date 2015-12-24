#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <glm/glm.hpp>
#include "texture.h"

class Block {
  public:
    Block(const std::string& fileName, const glm::vec3& pos, 
          const glm::vec3& rot):
      m_texture(fileName),
      m_position(pos),
      m_rotation(rot) {
    }

    inline Texture& GetTex() { return m_texture; }
    inline glm::vec3& GetPos() { return m_position; }
    inline glm::vec3& GetRot() { return m_rotation; }

    ~Block() {}
  protected:
  private:
    Texture m_texture;
    glm::vec3 m_position;
    glm::vec3 m_rotation; 
};

#endif // BLOCK_H
