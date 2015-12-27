#ifndef CUBE_H
#define CUBE_H

#include "block.h"
#include "texture.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"

enum Dim {
  X = 0,
  Y = 1,
  Z = 2
};

class Cube {
  public:
    Cube(int size);

    void SetRotation(Dim axis, int n, bool clockwise);

    void SetRandRotation();
    
    void UpdateRotation();
    
    void Draw(Shader &shader, Transform &transform, Camera &camera, Mesh &mesh);
    
    inline Texture& GetTex(int x, int y, int z) { 
      return blocks[x][y][z]->GetTex(); 
    }
    inline glm::vec3& GetPos(int x, int y, int z) { 
      return blocks[x][y][z]->GetPos(); 
    }
    inline glm::mat4& GetRot(int x, int y, int z) { 
      return blocks[x][y][z]->GetRot(); 
    }

    ~Cube();
  protected:
  private:
    int size;
    Block* blocks[3][3][3];

    bool currRotating;
    Dim  currRotateAxis;
    int  currRotateN;
    bool currRotateClockwise;
    int  currRotateSteps;
};

#endif // CUBE_H
