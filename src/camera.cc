/**
 * @file camera.cc
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the implementation of camera object.
 */

#include <glm/gtx/transform.hpp>
#include "../include/camera.h"

Camera::Camera(float fov, float aspect, float zNear, float zFar, float dist) {
  m_perspective = glm::perspective(fov, aspect, zNear, zFar);
  m_position = glm::vec3(0.0f, 0.0f, 0.0f);
  m_forward = glm::vec3(0.0f, 0.0f, 1.0f);
  m_up = glm::vec3(0.0f, 1.0f, 0.0f);
  m_horizOffset = 5.0f * (PI / 16.0f);
  m_vertOffset = PI / 4.0f;
  m_dist = dist;
}

void Camera::PositionCam() {
    float sinHoriz = sinf(m_horizOffset);
    float cosHoriz = cosf(m_horizOffset);
    m_position.x = m_dist * sinHoriz;
    m_position.z = m_dist * cosHoriz;
    m_forward.x = -sinHoriz;
    m_forward.z = -cosHoriz;

    float sinVert = sinf(m_vertOffset);
    m_position.y = m_dist * sinVert;
    m_forward.y = -sinVert;
}
    
glm::vec3 Camera::GetPickRay(float x, float y) {
  glm::mat4 view = glm::lookAt(m_position, m_position + m_forward, m_up);
  glm::vec4 viewport = glm::vec4(0, 0, 800, 600);
  glm::vec3 rayEnd   = glm::unProject(glm::vec3(x, 600.0f - y, 1.0f),
                                      view, m_perspective, viewport);
  return normalize(rayEnd - m_position);
}
