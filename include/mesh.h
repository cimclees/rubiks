/**
 * @file mesh.h
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the declerations of an OpenGL 3D object mesh class, as
 * well as a the implementation of a 3D vertex class that is used for meshes.
 */

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../lib/obj_loader.h"

/**
 * A 3D vertex classed to be used by the main mesh class of this file.
 */
class Vertex {
  public:
    /**
     * Constructor for a vertex.
     *
     * @param pos The intial position of the vertex.
     * @param texCoord Texture coordinates to be mapped to vertex.
     * @param normal Normal vector to be used for lighting.
     */
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord, 
           const glm::vec3& normal = glm::vec3(0,0,0)) {
      this->pos = pos;
      this->texCoord = texCoord;
      this->normal = normal;
    }
    
    /**
     * Get the position of a vertex.
     *
     * @return The position.
     */
    inline glm::vec3* GetPos() { return &pos; }

    /**
     * Get the texture coordinates of a vertex.
     *
     * @return the texture coordinates.
     */
    inline glm::vec2* GetTexCoord() { return &texCoord; }

    /**
     * Get the normal vector of a vertex.
     *
     * @return the normal vector.
     */
    inline glm::vec3* GetNormal() { return & normal; }
  protected:
  private:
    glm::vec3 pos;      // Position of vertex
    glm::vec2 texCoord; // Texture coordinate (pixel) to map to vertex
    glm::vec3 normal;   // Up direction on a surface
};

/**
 * Main mesh class.
 */
class Mesh {
  public:
    /**
     * Construct a mesh object from vertex data.
     *
     * @param vertices The vertices of the mesh.
     * @param numVertices The number of vertices.
     * @param indices
     * @param numIndices The number of indices.
     */
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices,
         unsigned int numIndices);

    /**
     * Construct a mesh object from an OBJ file.
     *
     * @param filename The OBJ file to load.
     */
    Mesh(const std::string& fileName);

    /**
     * Render a mesh object using active texture.
     */
    void Draw();

    /**
     * Destructor for a mesh.
     */
    ~Mesh();
  protected:
  private:
    /**
     * Initialize a mesh in OpenGL.
     *
     * @param model Mesh data: positions, texture coordinates, normals, indices.
     */
    void InitMesh(const IndexedModel& model);

    /**
     * @enum OpenGL data buffers for an initialized mesh.
     */
    enum {
      POSITION_VB,
      TEXCOORD_VB,
      NORMAL_VB,
      INDEX_VB,

      NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif // MESH_H
