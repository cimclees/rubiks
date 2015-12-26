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

void Cube::Rotate(int z) {
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      blocks[x][y][z]->GetRot().z += 0.01;
      
      if (x != 1 || y != 1) {
        float hyp = sqrt(pow(blocks[x][y][z]->GetPos().x, 2) + 
                         pow(blocks[x][y][z]->GetPos().y, 2));
        
        if (blocks[x][y][z]->GetPos().x < 0) {
          hyp = hyp * -1;
        }

        float theta1 = atan(blocks[x][y][z]->GetPos().y / 
                            blocks[x][y][z]->GetPos().x);
        
        blocks[x][y][z]->GetPos().x = hyp * cos( theta1 + 0.01 );
        blocks[x][y][z]->GetPos().y = hyp * sin( theta1 + 0.01 );
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
