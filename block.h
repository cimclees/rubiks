#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "texture.h"

class Block {
  public:
    Block(const std::string& fileName, const glm::vec3& pos, 
          const glm::vec3& rot):
      m_texture(fileName),
      m_position(pos),
      m_rotation() {
      
      glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1,0,0));
      glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0,1,0));
      glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0,0,1));

      m_rotation = rotZMatrix * rotYMatrix * rotXMatrix;
    }
    
    inline void RotX(const float& angle) {
      glm::mat4 rotXMatrix = glm::rotate(angle, glm::vec3(1,0,0));
      m_rotation = rotXMatrix * m_rotation;
    }

    inline void RotY(const float& angle) {
      glm::mat4 rotYMatrix = glm::rotate(angle, glm::vec3(0,1,0));
      m_rotation = rotYMatrix * m_rotation;
    }

    inline void RotZ(const float& angle) {
      glm::mat4 rotZMatrix = glm::rotate(angle, glm::vec3(0,0,1));
      m_rotation = rotZMatrix * m_rotation;
    }

    inline Texture& GetTex() { return m_texture; }
    inline glm::vec3& GetPos() { return m_position; }

    inline glm::mat4& GetRot() { return m_rotation; }

    ~Block() {}
  protected:
  private:
    Texture m_texture;
    glm::vec3 m_position;

    glm::mat4 m_rotation; 
};

#endif // BLOCK_H
