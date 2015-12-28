/**
 * @file cube.h
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the declerations of an object representing a Rubik's cube.
 */

#ifndef CUBE_H
#define CUBE_H

#include "block.h"
#include "texture.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"

const float PI = 3.141592653f;

/**
 * @enum Dimensions of rotation and translation.
 */
enum Dim {
  X = 0,
  Y = 1,
  Z = 2
};

class Cube {
  public:
    /**
     * Constructor for a cube.
     *
     * @param size Size of each dimension of the cube, i.e. the cube will be
     *    made up of a size*size*size collection of blocks.
     */
    Cube(int size);

    /**
     * Start a new rotation on a cube. Does nothing if the cube is already
     * rotating.
     *
     * @param axis Axis about which to rotate.
     * @param n Slab of blocks between 0 and size to be rotated.
     * @param clockwise Rotate clockwise if true, counterclockwise if false.
     */
    void SetRotation(Dim axis, int n, bool clockwise);

    /**
     * Start a new rotation on a cube with randomly properties.
     */
    void SetRandRotation();
    
    /**
     * Update position and rotation values of blocks on a cube according to an 
     * ongoing rotation.
     */
    void UpdateRotation();
    
    /**
     * Draw a cube to output.
     *
     * @param shader A shader.
     * @param transform A transform.
     * @param camera A camera.
     * @param mesh A mesh.
     */
    void Draw(Shader &shader, Transform &transform, Camera &camera, Mesh &mesh);
    
    /**
     * Get the texture associated with a block on a cube.
     *
     * @param x Position of desired block on cube along x-axis.
     * @param y Position of desired block on cube along y-axis.
     * @param z Position of desired block on cube along z-axis.
     * @return The associated texture object.
     */
    inline Texture& GetTex(int x, int y, int z) { 
      return blocks[x][y][z]->GetTex(); 
    }
    
    /**
     * Get the spacial position of a block on a cube.
     *
     * @param x Position of desired block on cube along x-axis.
     * @param y Position of desired block on cube along y-axis.
     * @param z Position of desired block on cube along z-axis.
     * @return The position of the block.
     */
    inline glm::vec3& GetPos(int x, int y, int z) { 
      return blocks[x][y][z]->GetPos(); 
    }
    
    /**
     * Get the rotation matrix of a block on a cube.
     *
     * @param x Position of desired block on cube along x-axis.
     * @param y Position of desired block on cube along y-axis.
     * @param z Position of desired block on cube along z-axis.
     * @return The rotation matrix of the block.
     */
    inline glm::mat4& GetRot(int x, int y, int z) { 
      return blocks[x][y][z]->GetRot(); 
    }

    /**
     * Descructor for a cube.
     */
    ~Cube();
  protected:
  private:
    int size;
    Block* blocks[3][3][3];

    bool currRotating;
    Dim  currRotateAxis;
    int  currRotateN;
    bool currRotateClockwise;
    int  currRotateSteps;
};

#endif // CUBE_H
