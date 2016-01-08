/**
 * @file block.h
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the declerations of an object representing a single block
 * of a Rubik's Cube.
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "./texture.h"

/**
 * @enum Color combinations possible for blocks.
 */
enum Col {
  BLK = 0,
  WHT,
  RED,
  BLU,
  ORG,
  GRN,
  YLW,
  WHTRED,
  WHTBLU,
  WHTORG,
  WHTGRN,
  REDBLU,
  REDGRN,
  REDYLW,
  BLUORG,
  BLUYLW,
  ORGGRN,
  ORGYLW,
  GRNYLW,
  WHTREDBLU,
  WHTREDGRN,
  WHTBLUORG,
  WHTORGGRN,
  REDBLUYLW,
  REDGRNYLW,
  BLUORGYLW,
  ORGGRNYLW,

  NUM_COLORS
};

class Block {
  public:
    /**
     * Constructor for a block.
     *
     * @param color The color combination of the block.
     * @param pos Initial position of the block.
     * @param rot Initial rotation of the block.
     */
    Block(Col color, const glm::vec3& pos, const glm::vec3& rot);
    
    /**
     * Rotate a block along the x-axis, about its position.
     *
     * @param angle Amount of rotation.
     */
    void RotX(const float& angle);

    /**
     * Rotate a block along the y-axis, about its position.
     *
     * @param angle Amount of rotation.
     */
    void RotY(const float& angle);

    /**
     * Rotate a block along the z-axis, about its position.
     *
     * @param angle Amount of rotation.
     */
    void RotZ(const float& angle);

    /**
     * Get the color of a block.
     *
     * @return The color.
     */
    inline Col& GetCol() { return m_color; }
    
    /**
     * Get the position of a block.
     *
     * @return The position.
     */
    inline glm::vec3& GetPos() { return m_position; }
    
    /**
     * Get the rotation matrix of a block.
     *
     * @return The rotation matrix.
     */
    inline glm::mat4& GetRot() { return m_rotation; }
  protected:
  private:
    Col m_color;
    glm::vec3 m_position;
    glm::mat4 m_rotation; 
};

#endif // BLOCK_H
