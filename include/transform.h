/**
 * @file transform.h
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the implementation of a simple transform class.
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform {
  public:
    /**
     * Constructor for a transform object.
     *
     * @param pos Initial position to use for transform.
     * @param scale Initial scale to use for transform.
     */
    Transform(const glm::vec3& pos   = glm::vec3(), 
              const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
      m_pos(pos),
      m_rotMat(),
      m_scale(scale) {
    }
    
    /**
     * Get a model matrix to contain position, scale, and rotation information.
     *
     * @return The model matrix.
     */
    inline glm::mat4 GetModel() const {
      glm::mat4 posMatrix = glm::translate(m_pos);
      glm::mat4 scaleMatrix = glm::scale(m_scale);
      
      return posMatrix * m_rotMat * scaleMatrix;
    }
   
    /**
     * Set the position of an object.
     * 
     * @param pos The new position.
     */ 
    inline void SetPos(const glm::vec3& pos) { m_pos = pos; }


    /**
     * Set the rotation of an object.
     *
     * @param rot The new rotation matrix.
     */
    inline void SetRot(const glm::mat4& rot) { m_rotMat = rot; }

    /**
     * Set the scale of an object.
     *
     * @param scale The new scale.
     */
    inline void SetScale(const glm::vec3& scale) { m_scale = scale; }
  protected:
  private:
    glm::vec3 m_pos;
    glm::mat4 m_rotMat;
    glm::vec3 m_scale;
};

#endif // TRANSFORM_H
