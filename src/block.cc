/**
 * @file block.cc
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the implementation of an object representing a single 
 * block of a Rubik's Cube.
 */

#include "../include/block.h"

Block::Block(Col color, const glm::vec3& pos, const glm::vec3& rot):
  m_position(pos),
  m_rotation() {
 
  m_color = color; 
  glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1,0,0));
  glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0,1,0));
  glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0,0,1));
  m_rotation = rotZMatrix * rotYMatrix * rotXMatrix;
}

void Block::RotX(const float& angle) {
  glm::mat4 rotXMatrix = glm::rotate(angle, glm::vec3(1,0,0));
  m_rotation = rotXMatrix * m_rotation;
}

void Block::RotY(const float& angle) {
  glm::mat4 rotYMatrix = glm::rotate(angle, glm::vec3(0,1,0));
  m_rotation = rotYMatrix * m_rotation;
}

void Block::RotZ(const float& angle) {
  glm::mat4 rotZMatrix = glm::rotate(angle, glm::vec3(0,0,1));
  m_rotation = rotZMatrix * m_rotation;
}
