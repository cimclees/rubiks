#include "cube.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

Cube::Cube(int size = 3) {
  this->size = size;
  this->currRotating = false;
  this->currRotateAxis = X;
  this->currRotateN = 0;
  this->currRotateClockwise = true;
  this->currRotateSteps = 0;

  // this->blocks = new Block* blocks[size][size][size];
  for (int z = 0; z < size; z++) {
    for (int y = 0; y < size; y++) {
      for (int x = 0; x < size; x++) {
        blocks[x][y][z] = new Block("./res/block_uv_1.png", 
                                    glm::vec3(2*(x - 1), 2*(y - 1), 2*(z - 1)),
                                    glm::vec3(0, 0, 0));
      }
    }
  }
}

void Cube::SetRotation(Dim axis, int n, bool clockwise) {
  if (!currRotating) {
    this->currRotating = true;
    this->currRotateAxis = axis;
    this->currRotateN = n;
    this->currRotateClockwise = clockwise;
    this->currRotateSteps = 300;
  }
}

void Cube::SetRandRotation() {
  Dim axis = static_cast<Dim>(rand() % 3);
  int n = rand() % size;
  bool clockwise = (bool) (rand() % 2);
  SetRotation(axis, n, clockwise);
}

void Cube::UpdateRotation() {

  if (currRotating) {
    int x_min = 0, y_min = 0, z_min = 0;
    int x_max = 2, y_max = 2, z_max = 2;
    
    // Choose correct blocks to rotate 
    switch(currRotateAxis) {
      case X: {
        x_min = currRotateN;
        x_max = currRotateN;
        break;
      }
      case Y: {
        y_min = currRotateN;
        y_max = currRotateN;
        break;
      }
      case Z: {
        z_min = currRotateN;
        z_max = currRotateN;
        break;
      }
    }
    
    // bool rotationComplete = false;
    // Rotate blocks
    for (int x = x_min; x <= x_max; x++) {
      for (int y = y_min; y <= y_max; y++) {
        for (int z = z_min; z <= z_max; z++) {
          // Choose position and rotation values to be modified
          
          float PI = 3.141592653f;
          // Update relevant rotation value
          float deltaRot = (PI / 2) / 300.0f;
          if (!currRotateClockwise) {
            deltaRot *= -1.0f;
          }
          //*rot += deltaRot;
          
          // float* rot;
          float* adj;
          float* opp;
          bool notCenter;
          switch(currRotateAxis) {
            case X: {
              // rot = &blocks[x][y][z]->GetRot().x;
              blocks[x][y][z]->RotX(deltaRot);

              adj = &blocks[x][y][z]->GetPos().y;
              opp = &blocks[x][y][z]->GetPos().z;
              notCenter = (y != 1 || z != 1);
              break;
            }
            case Y: {
              // rot = &blocks[x][y][z]->GetRot().y;
              blocks[x][y][z]->RotY(deltaRot);

              adj = &blocks[x][y][z]->GetPos().z;
              opp = &blocks[x][y][z]->GetPos().x;
              notCenter = (x != 1 || z != 1);
              break;
            }
            case Z: {
              // rot = &blocks[x][y][z]->GetRot().z;
              blocks[x][y][z]->RotZ(deltaRot);

              adj = &blocks[x][y][z]->GetPos().x;
              opp = &blocks[x][y][z]->GetPos().y;
              notCenter = (x != 1 || y != 1);
              break;
            }
          }

          // Update relevant position values
          if (notCenter) {
            float hyp = sqrt(pow(*adj, 2) + pow(*opp, 2));
            if (*adj < 0) {
              hyp = hyp * -1.0f;
            }
            float theta1 = atan(*opp / *adj);
            *adj = hyp * cos( theta1 + deltaRot );
            *opp = hyp * sin( theta1 + deltaRot );
          }
          
          /*
          if (fabs(fabs(*rot) - (PI / 2.0f)) < 0.0001f ||
              fabs(fabs(*rot) - PI) < 0.0001f ||
              fabs(fabs(*rot) - (3.0f * PI / 2.0f)) < 0.0001f) {

            rotationComplete = true;

          } else if (fabs(fabs(*rot) - (2.0f * PI)) < 0.0001f) {
            rotationComplete = true;
            *rot = 0.0f;
          }
          */

        }
      }
    }

    currRotateSteps--;
          
    // Check rotation completion
    if (currRotateSteps == 0) {
      this->currRotating = false;
      
      Block* tempBlocks[3][3][3];
      for (int x = x_min; x <= x_max; x++) {
        for (int y = y_min; y <= y_max; y++) {
          for (int z = z_min; z <= z_max; z++) {
            switch(currRotateAxis) {
              case X: {
                if (currRotateClockwise) {
                  tempBlocks[x][y][z] = blocks[x][z][2 - y];
                } else {
                  tempBlocks[x][y][z] = blocks[x][2 - z][y];
                }
                break;
              }
              case Y: {
                if (currRotateClockwise) {
                  tempBlocks[x][y][z] = blocks[2 - z][y][x];
                } else {
                  tempBlocks[x][y][z] = blocks[z][y][2 - x];
                }
                break;
              }
              case Z: {
                if (currRotateClockwise) {
                  tempBlocks[x][y][z] = blocks[y][2 - x][z];
                } else {
                  tempBlocks[x][y][z] = blocks[2 - y][x][z];
                }
                break;
              }
            }
           

          }
        }
      }
      
      for (int x = x_min; x <= x_max; x++) {
        for (int y = y_min; y <= y_max; y++) {
          for (int z = z_min; z <= z_max; z++) {
            blocks[x][y][z] = tempBlocks[x][y][z];
          }
        }
      }


    }
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

        shader.Update(transform, camera);
        mesh.Draw();
      }
    }
  }
}

Cube::~Cube() {
  for (int z = 0; z < this->size; z++) {
    for (int y = 0; y < this->size; y++) {
      for (int x = 0; x < this->size; x++) {
        delete blocks[x][y][z];
      }
    }
  }
}
