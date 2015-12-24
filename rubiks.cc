#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "block.h"
#include <glm/glm.hpp>
#include <math.h>

#include <iostream>

#define WIDTH 800
#define HEIGHT 600


void rotate(Block* blocks[3][3][3], int z = 0) {
  
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
     
      double hyp = pow(blocks[x][y][z]->GetPos().x, 2) + 
                   pow(blocks[x][y][z]->GetPos().y, 2);
      
      // std::cout << "angle: " <<  << std::endl;

      /* 
      int yNegSwitch = 1;
      if (blocks[x][y][z]->GetPos().y > 0 ||
          (abs(blocks[x][y][z]->GetPos().y) < 0.001 
           &&  blocks[x][y][z]->GetPos().x < 0)) {

        blocks[x][y][z]->GetPos().x += 0.01;
        yNegSwitch = 1;
      } else {
        blocks[x][y][z]->GetPos().x -= 0.01;
        yNegSwitch = -1;
      }
      
      blocks[x][y][z]->GetPos().y = yNegSwitch * sqrt(hyp - pow(blocks[x][y][z]->GetPos().x, 2));
      */ 
      
      blocks[x][y][z]->GetRot().z += 0.01;
      // std::cout << blocks[x][y][z]->GetRot().z << std::endl;
      
      if (blocks[x][y][z]->GetPos().y > 0 || (blocks[x][y][z]->GetPos().y == 0 
                                              && blocks[x][y][z]->GetPos().x < 0)) {

        blocks[x][y][z]->GetPos().y = hyp * (sin(blocks[x][y][z]->GetRot().z - 0.01) -
                                             sin(blocks[x][y][z]->GetRot().z));
        
        blocks[x][y][z]->GetPos().x = hyp * (cos(blocks[x][y][z]->GetRot().z) -
                                             cos(blocks[x][y][z]->GetRot().z - 0.01));
      
        } else {

      }


   


    }
  }
}

int main() {

  Display display(WIDTH, HEIGHT, "Hello World!");

  Mesh blockMesh("./res/block.obj");
     
  Block* blocks[3][3][3];
  for (int z = 0; z < 3; z++) {
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 3; x++) {
        blocks[x][y][z] = new Block("./res/block_uv_1.png", 
                                    glm::vec3(2*(x - 1), 2*(y - 1), 2*z),
                                    glm::vec3(0, 0, 0));
      }
    }
  }
  
  // Texture texture1("./res/block_uv_1.png");

  Shader shader("./res/basicShader");
  
  Camera camera(glm::vec3(0,2,-15), 70.0f, ((float) WIDTH) / HEIGHT, 
                0.01f, 1000.0f);
  
  Transform transform;
  
  float counter = 0.0f;

  while (!display.IsClosed()) {
    display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

    float sinCounter = sinf(counter);
    float cosCounter = cosf(counter);
    
    camera.GetPos().x = 20 * sinCounter;
    camera.GetPos().z = 20 * cosCounter;
    
    camera.GetFor().x = -sinCounter;
    camera.GetFor().z = -cosCounter;

    rotate(blocks);

    for (int z = 0; z < 3; z++) {
      for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
          shader.Bind();
          blocks[x][y][z]->GetTex().Bind(0);
          transform.SetPos( blocks[x][y][z]->GetPos() );
          transform.SetRot( blocks[x][y][z]->GetRot() );
          shader.Update(transform, camera);
          blockMesh.Draw();
        }
      }
    }

    // transform.GetPos().x = sinCounter;
    // transform.GetPos().z = cosCounter;
    // transform.GetRot().y = counter;
    // transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
    
    display.Update();
    
    counter += 0.01f;
  }

  for (int z = 0; z < 3; z++) {
    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 3; x++) {
        delete blocks[x][y][z];
      }
    }
  }

  return 0;
}
