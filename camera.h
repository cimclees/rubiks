#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera{
  public:
    Camera(const glm::vec3& pos, float fov, float aspect, 
           float zNear, float zFar) {
      m_perspective = glm::perspective(fov, aspect, zNear, zFar);
      m_position = pos;
      m_forward = glm::vec3(0,0,1);
      m_up = glm::vec3(0,1,0);
    }

    inline glm::vec3& GetPos() { return m_position; }
    inline glm::vec3& GetFor() { return m_forward; }

    inline glm::mat4 GetViewProjection() const {
      return m_perspective * glm::lookAt(m_position, 
                                         m_position + m_forward, m_up);
    }

    glm::vec3 GetPickRay(float x, float y) {
      glm::mat4 view = glm::lookAt(m_position, m_position + m_forward, m_up);
      glm::vec4 viewport = glm::vec4(0, 0, 800, 600);
      glm::vec3 rayEnd   = glm::unProject(glm::vec3(x, 600.0f - y, 1.0f),
                                view, m_perspective, viewport);
      return normalize(rayEnd - m_position);
    }


  protected:
  private:
    glm::mat4 m_perspective; // Projection
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;
};

#endif // CAMERA_H
