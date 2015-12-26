#ifndef CUBE_H
#define CUBE_H

#include "block.h"
#include "texture.h"

class Cube {
  public:
    Cube(int size);
    void Rotate(int z = 0);
    
    inline Texture& GetTex(int x, int y, int z) { 
      return blocks[x][y][z]->GetTex(); 
    }
    inline glm::vec3& GetPos(int x, int y, int z) { 
      return blocks[x][y][z]->GetPos(); 
    }
    inline glm::vec3& GetRot(int x, int y, int z) { 
      return blocks[x][y][z]->GetRot(); 
    }

    ~Cube();
  protected:
  private:
    int size;
    Block* blocks[3][3][3];
};

#endif // CUBE_H
