#include "cube.h"
#include <math.h>

Cube::Cube(int size = 3) {
  this->size = size;
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

void Cube::Rotate(Dim axis, int n) {
  int x_min = 0, y_min = 0, z_min = 0;
  int x_max = 2, y_max = 2, z_max = 2;
  
  // Choose correct blocks to rotate 
  switch(axis) {
    case X: {
      x_min = n;
      x_max = n;
      break;
    }
    case Y: {
      y_min = n;
      y_max = n;
      break;
    }
    case Z: {
      z_min = n;
      z_max = n;
      break;
    }
  }
  
  // Rotate blocks
  for (int x = x_min; x <= x_max; x++) {
    for (int y = y_min; y <= y_max; y++) {
      for (int z = z_min; z <= z_max; z++) {
        // Choose position and rotation values to be modified
        float* rot;
        float* adj;
        float* opp;
        bool notCenter;
        switch(axis) {
          case X: {
            rot = &blocks[x][y][z]->GetRot().x;
            adj = &blocks[x][y][z]->GetPos().y;
            opp = &blocks[x][y][z]->GetPos().z;
            notCenter = (y != 1 || z != 1);
            break;
          }
          case Y: {
            rot = &blocks[x][y][z]->GetRot().y;
            adj = &blocks[x][y][z]->GetPos().z;
            opp = &blocks[x][y][z]->GetPos().x;
            notCenter = (x != 1 || z != 1);
            break;
          }
          case Z: {
            rot = &blocks[x][y][z]->GetRot().z;
            adj = &blocks[x][y][z]->GetPos().x;
            opp = &blocks[x][y][z]->GetPos().y;
            notCenter = (x != 1 || y != 1);
            break;
          }
        }

        // Update relevant values
        *rot += 0.01f;
        if (notCenter) {
          float hyp = sqrt(pow(*adj, 2) + pow(*opp, 2));
          if (*adj < 0) {
            hyp = hyp * -1.0f;
          }
          float theta1 = atan(*opp / *adj);
          *adj = hyp * cos( theta1 + 0.01f );
          *opp = hyp * sin( theta1 + 0.01f );
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
