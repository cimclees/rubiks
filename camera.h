/**
 * @file camera.h
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the declerations of camera object.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera{
  public:
    /**
     * Constructor for a camera object.
     *
     * @param fov The field of view of the camera.
     * @param aspect The aspect ratio of the program window (and camera).
     * @param zNear Objects closer to the camera than zNear are not drawn.
     * @param zFar Objects further from the camera than zFar are not drawn.
     */
    Camera(float fov, float aspect, float zNear, float zFar);
    
    /**
     * Get the position of a camera in 3D space.
     *
     * @return The position of the camera.
     */
    inline glm::vec3& GetPos() { return m_position; }

    /**
     * Get the direction a camera is facing.
     *
     * @return The forward direction relative to the camera.
     */
    inline glm::vec3& GetFor() { return m_forward; }

    /**
     * Get the projection view matrix of a camera.
     *
     * @return The projection view matrix.
     */
    inline glm::mat4 GetViewProjection() const {
      return m_perspective * glm::lookAt(m_position, 
                                         m_position + m_forward, m_up);
    }

    /**
     * Function to position and orient a camera so that it always faces the 
     * origin.
     *
     * @param horizOffset Value used to compute position on x and z axes.
     * @param vertOffset  Value used to compute position on y axis.
     */
    void PositionCam(const float& horizOffset, const float& vertOffset);
    
    /**
     * Function to project a mouse click into the program's 3D space through
     * the camera.
     *
     * @param x Horizontal location of mouse click on program window.
     * @param y Vertical location of mouse click on program window.
     * @return A normalized vector representing the direction of the location
     *    of the mouse flick relative to the camera position.
     */
    glm::vec3 GetPickRay(float x, float y);

  protected:
  private:
    glm::mat4 m_perspective; // Projection
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;
};

#endif // CAMERA_H
