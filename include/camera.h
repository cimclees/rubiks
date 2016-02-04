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

const float PI = 3.141592653f;

class Camera{
  public:
    /**
     * Constructor for a camera object.
     *
     * @param fov The field of view of the camera.
     * @param aspect The aspect ratio of the program window (and camera).
     * @param zNear Objects closer to the camera than zNear are not drawn.
     * @param zFar Objects further from the camera than zFar are not drawn.
     * @param dist The distance from the origin the camera should be.
     */
    Camera(float fov, float aspect, float zNear, float zFar, float dist);

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
     * Get the horizontal offset of the camera.  Offset values are used to 
     * position the camera so that it always faces the origin.
     *
     * @return The horizontal offset of the camera.
     */
    inline float& GetHoriz() { return m_horizOffset; }

    /**
     * Get the vertical offset of the camera.  Offset values are used to 
     * position the camera so that it always faces the origin.
     *
     * @return The vertical offset of the camera.
     */
    inline float& GetVert() { return m_vertOffset; }

    /**
     * Function to position and orient a camera so that it always faces the 
     * origin, according to horizontal and vertical offset values accessed
     * by GetHoriz and GetVert.
     */
    void PositionCam();

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
    glm::mat4 m_perspective;  // Projection
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;
    float m_horizOffset;
    float m_vertOffset;
    float m_dist;
};

#endif  // CAMERA_H
