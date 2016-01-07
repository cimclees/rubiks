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

#include <vector>
#include "block.h"
#include "texture.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"

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
     * Function to choose correct rotation to make on X or Z axes depending on
     * orientation at which a cube is viewed, and carry out that rotation.
     *
     * @param absZgreaterX The dimension of rotation to be used when the 
     *    absolute value of the z component of the forward direction vector
     *    is greater than the absolute value of the x component of the forward
     *    direction vector.
     * @param ZgreatX True if rotation to be clockwise when the value of
     *   the z component of the forward direction vector is greater than the 
     *   absolute value of the x component of the forward direction vector.
     * @param XgreatZ True if rotation to be clockwise when the value of
     *   the x component of the forward direction vector is greater than the 
     *   absolute value of the z component of the forward direction vector.
     * @param foward The forward direction vector from which the cube is viewed.
     */
    void RotateXZ(Dim absZgreaterX, bool ZgreatX, bool XgreatZ,
                  glm::vec3& forward);

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
     * Select the first block on a cube to intersect a ray.  Unselect a block
     * if no block interesects the ray.
     *
     * @param rayStart The origin of the ray.
     * @param rayDir The direction of the ray (should be normalized).
     */
    void SelectBlock(const glm::vec3& rayStart, const glm::vec3& rayDir);

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
     * Get the selected block on a cube.
     *
     * @return The position on the cube of the selected block.
     */
    inline glm::vec3& GetSelected() { 
      return selected; 
    }
    
    /**
     * Descructor for a cube.
     */
    ~Cube();
  protected:
  private:
    int size;
    std::vector< std::vector< std::vector <Block*> > > blocks;
    Texture* m_textures;

    // Rotation data
    Dim  currRotateAxis;
    int  currRotateN;
    bool currRotateClockwise;
    int  currRotateSteps;

    glm::vec3 selected;
};

#endif // CUBE_H
