#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "obj_loader.h"

class Vertex {
  public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord) {
      this->pos = pos;
      this->texCoord = texCoord;
    }

    inline glm::vec3* GetPos() { return &pos; }
    inline glm::vec2* GetTexCoord() { return &texCoord; }
  protected:
  private:
    glm::vec3 pos;      // Position of vertex
    glm::vec2 texCoord; // Texture coordinate (pixel) to map to vertex
};

class Mesh {
  public:
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices,
         unsigned int numIndices);

    Mesh(const std::string& fileName);

    void Draw();

    virtual ~Mesh();
  protected:
  private:
    Mesh(const Mesh& other);
    void operator=(const Mesh& other);

    void InitMesh(const IndexedModel& model);

    enum {
      POSITION_VB,
      TEXCOORD_VB,

      INDEX_VB,

      NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif // MESH_H
