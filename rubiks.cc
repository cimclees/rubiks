#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "block.h"
#include "cube.h"

#define WIDTH 800
#define HEIGHT 600

int main() {

  Display display(WIDTH, HEIGHT, "Hello World!");

  Mesh blockMesh("./res/block.obj");
     
  Shader shader("./res/basicShader");
  
  Camera camera(glm::vec3(0,2,-20), 70.0f, ((float) WIDTH) / HEIGHT, 
                0.01f, 1000.0f);
  
  Transform transform;

  Cube cube(3);
  cube.SetRandRotation();
  
  float counter = 0.0f;

  while (!display.IsClosed()) {
    display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

    float sinCounter = sinf(counter);
    float cosCounter = cosf(counter);
     
    camera.GetPos().x = 20 * sinCounter;
    camera.GetPos().z = 20 * cosCounter;
   
    camera.GetFor().x = -sinCounter;
    camera.GetFor().z = -cosCounter;
    
    cube.UpdateRotation();

    cube.SetRandRotation();
    
    cube.Draw(shader, transform, camera, blockMesh);

    display.Update();
    
    counter += 0.01f;
  }

  return 0;
}
