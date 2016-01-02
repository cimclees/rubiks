/**
 * @file cube.cc
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the implementation of an object representing a 
 * Rubik's cube.
 */

#include <cmath>
#include <cstdlib>
#include "cube.h"

#define ROTATION_FRAMES 60

Cube::Cube(int size) :
  blocks(size, std::vector<std::vector<Block*> >
      (size, std::vector<Block*>(size))) {
  this->size = size;
  this->currRotateAxis = X;
  this->currRotateN = 0;
  this->currRotateClockwise = true;
  this->currRotateSteps = 0;
  this->selected = glm::vec3(-1, -1, -1); // No cube selected
  
  float posOffset = (static_cast<float>(size) - 1.0f) / 2.0f;
  // Create blocks on cube.
  for (int z = 0; z < size; z++) {
    for (int y = 0; y < size; y++) {
      for (int x = 0; x < size; x++) {
        blocks[x][y][z] = new Block("./res/block_uv_1.png", 
                                    glm::vec3(2*(x - posOffset), 
                                              2*(y - posOffset), 
                                              2*(z - posOffset)),
                                    glm::vec3(0, 0, 0));
      }
    }
  }
}

void Cube::SetRotation(Dim axis, int n, bool clockwise) {
  if (currRotateSteps == 0 && n >= 0 && n < size) {
    currRotateAxis = axis;
    currRotateN = n;
    currRotateClockwise = clockwise;
    currRotateSteps = ROTATION_FRAMES;
  }
}

void Cube::SetRandRotation() {
  Dim axis = static_cast<Dim>(rand() % 3);
  int n = rand() % size;
  bool clockwise = (bool) (rand() % 2);
  SetRotation(axis, n, clockwise);
}

void Cube::UpdateRotation() {
  if (currRotateSteps != 0) {
    int x_min = 0, y_min = 0, z_min = 0;
    int x_max = size, y_max = size, z_max = size;
    
    // Choose correct blocks to rotate.
    switch(currRotateAxis) {
      case X: {
        x_min = currRotateN;
        x_max = currRotateN + 1;
        break;
      }
      case Y: {
        y_min = currRotateN;
        y_max = currRotateN + 1;
        break;
      }
      case Z: {
        z_min = currRotateN;
        z_max = currRotateN + 1;
        break;
      }
    }
    
    // Rotate blocks.
    for (int x = x_min; x < x_max; x++) {
      for (int y = y_min; y < y_max; y++) {
        for (int z = z_min; z < z_max; z++) {
          
          // Determine angle of rotation.
          float deltaRot = (PI / 2) / ROTATION_FRAMES;
          if (!currRotateClockwise) {
            deltaRot *= -1.0f;
          }
          
          // Choose position values to be modified and update rotation.
          float* adj;
          float* opp;
          bool center;
          int middleIndex = (size - 1) / 2;
          switch(currRotateAxis) {
            case X: {
              blocks[x][y][z]->RotX(deltaRot);
              adj = &blocks[x][y][z]->GetPos().y;
              opp = &blocks[x][y][z]->GetPos().z;
              center = (size % 2 == 1 && y ==  middleIndex && z == middleIndex);
              break;
            }
            case Y: {
              blocks[x][y][z]->RotY(deltaRot);
              adj = &blocks[x][y][z]->GetPos().z;
              opp = &blocks[x][y][z]->GetPos().x;
              center = (size % 2 == 1 && x ==  middleIndex && z == middleIndex);
              break;
            }
            case Z: {
              blocks[x][y][z]->RotZ(deltaRot);
              adj = &blocks[x][y][z]->GetPos().x;
              opp = &blocks[x][y][z]->GetPos().y;
              center = (size % 2 == 1 && x ==  middleIndex && y == middleIndex);
              break;
            }
          }

          // Update relevant position values.
          if (!center) {
            float hyp = sqrt(pow(*adj, 2) + pow(*opp, 2));
            if (*adj < 0) {
              hyp = hyp * -1.0f;
            }
            float theta1 = atan(*opp / *adj);
            *adj = hyp * cos( theta1 + deltaRot );
            *opp = hyp * sin( theta1 + deltaRot );
          }
        }
      }
    }
    
    // Keep track of amount of rotation.
    currRotateSteps--;
          
    // Check rotation completion.
    if (currRotateSteps == 0) {
 
      // Update block positions on cube.     
      int translate = size - 1;
      std::vector< std::vector< std::vector <Block*> > > tempBlocks(size, 
        std::vector<std::vector<Block*> >(size, std::vector<Block*>(size)));
      for (int x = x_min; x < x_max; x++) {
        for (int y = y_min; y < y_max; y++) {
          for (int z = z_min; z < z_max; z++) {
            switch(currRotateAxis) {
              case X: {
                if (currRotateClockwise) {
                  tempBlocks[x][y][z] = blocks[x][z][translate - y];
                } else {
                  tempBlocks[x][y][z] = blocks[x][translate - z][y];
                }
                break;
              }
              case Y: {
                if (currRotateClockwise) {
                  tempBlocks[x][y][z] = blocks[translate - z][y][x];
                } else {
                  tempBlocks[x][y][z] = blocks[z][y][translate - x];
                }
                break;
              }
              case Z: {
                if (currRotateClockwise) {
                  tempBlocks[x][y][z] = blocks[y][translate - x][z];
                } else {
                  tempBlocks[x][y][z] = blocks[translate - y][x][z];
                }
                break;
              }
            }
          }
        }
      }
      for (int x = x_min; x < x_max; x++) {
        for (int y = y_min; y < y_max; y++) {
          for (int z = z_min; z < z_max; z++) {
            blocks[x][y][z] = tempBlocks[x][y][z];
          }
        }
      }
      
      // Update selected block
      switch(currRotateAxis) {
        case X: {
          if (selected.x == currRotateN) {
            if (currRotateClockwise) {
              selected = glm::vec3(selected.x, translate - selected.z, selected.y);
            } else {
              selected = glm::vec3(selected.x, selected.z, translate - selected.y);
            }
          }
          break;
        }
        case Y: {
          if (selected.y == currRotateN) {
            if (currRotateClockwise) {
              selected = glm::vec3(selected.z, selected.y, translate - selected.x);
            } else {
              selected = glm::vec3(translate - selected.z, selected.y, selected.x);
            }
          }
          break;
        }
        case Z: {
          if (selected.z == currRotateN) {
            if (currRotateClockwise) {
              selected = glm::vec3(translate - selected.y, selected.x, selected.z);
            } else {
              selected = glm::vec3(selected.y, translate - selected.x, selected.z);
            }
          break;
          }
        }
      }
    }
  }
}
    
void RotateXZ(Dim absZgreaterX, bool ZgreatX, bool XgreatZ,
              glm::vec3& forward) {
  Dim absXgreaterZ;
  int absZgreaterXn;
  int absXgreaterZn;

  if (absZgreaterX == Z) {
    absZgreaterXn = GetSelected().z;
    absXgreaterZ = X;
    absXgreaterZn = GetSelected().x;
  } else {
    absZgreaterXn = GetSelected().x;
    absXgreaterZ = Z;
    absXgreaterZn = GetSelected().z;
  }

  if (forward.z > fabs(forward.x)) {
    SetRotation(absZgreaterX, absZgreaterXn, ZgreatX);
  } else if (forward.z < -1.0f * fabs(forward.x)) {
    SetRotation(absZgreaterX, absZgreaterXn, !ZgreatX);
  } else if (forward.x > fabs(forward.z)) {
    SetRotation(absXgreaterZ, absXgreaterZn, XgreatZ);
  } else if (forward.x < -1.0f * fabs(forward.z)) {
    SetRotation(absXgreaterZ, absXgreaterZn, !XgreatZ);
  }
}

void Cube::Draw(Shader &shader, Transform &transform, 
                Camera &camera, Mesh &mesh) { 
  for (int z = 0; z < size; z++) {
    for (int y = 0; y < size; y++) {
      for (int x = 0; x < size; x++) {
        shader.Bind();
        this->GetTex(x, y, z).Bind(0);
        transform.SetPos( this->GetPos(x, y, z) );
        transform.SetRot( this->GetRot(x, y, z) );
        
        if (this->GetSelected() == glm::vec3(x, y, z)) {
          transform.SetScale( glm::vec3(1.2f, 1.2f, 1.2f) );
        } else {
          transform.SetScale( glm::vec3(1.0f, 1.0f, 1.0f) );
        }
        
        shader.Update(transform, camera);
        mesh.Draw();
      }
    }
  }
}

void Cube::SelectBlock(const glm::vec3& rayStart, const glm::vec3& rayDir) {
  // Small incrememnts for collision check.
  glm::vec3 delta = rayDir / 100.0f;

  // Ray collision check.
  glm::vec3 currPoint(rayStart);
  bool found = false;

  int x = 0;
  int y = 0;
  int z = 0;

  // Get close to cube.
  while (fabs(currPoint.x) > size + 0.1f &&
         fabs(currPoint.y) > size + 0.1f &&
         fabs(currPoint.z) > size + 0.1f) {
    currPoint += delta;
  }

  // Iterate over points on ray.
  while (!found && (    fabs(currPoint.x) < size + 0.2f
                    ||  fabs(currPoint.y) < size + 0.2f
                    ||  fabs(currPoint.z) < size + 0.2f)) {

    currPoint += delta;
  
    // Check point collision with any block.
    for (x = 0; x < size && !found; x++) {
      for (y = 0; y < size && !found; y++) {
        for (z = 0; z < size && !found; z++) {
            if ( fabs(GetPos(x, y, z).x - currPoint.x) < 1.0f
              && fabs(GetPos(x, y, z).y - currPoint.y) < 1.0f
              && fabs(GetPos(x, y, z).z - currPoint.z) < 1.0f) {
            found = true;
            GetSelected() = glm::vec3(x, y, z);
          }
        }
      }
    }  
  }

  if (!found) {
    this->GetSelected() = glm::vec3(-1, -1, -1);
  }
}

Cube::~Cube() {
  for (int z = 0; z < size; z++) {
    for (int y = 0; y < size; y++) {
      for (int x = 0; x < size; x++) {
        delete blocks[x][y][z];
      }
    }
  }
}
