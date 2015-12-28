/**
 * @file rubiks.cc
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the main function for a Rubik's Cube game.
 */

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "transform.h"
#include "cube.h"

// Window size
#define WIDTH 800
#define HEIGHT 600

int main() {
  // Open a window.
  Display display(WIDTH, HEIGHT, "Rubik's Cube");
  // Load 3D data for a block model.
  Mesh blockMesh("./res/block.obj");
  //
  Shader shader("./res/basicShader");
  // Create a camera object to manipulate positional perspective.
  Camera camera(glm::vec3(0,2,-20), 70.0f, ((float) WIDTH) / HEIGHT, 
                0.01f, 1000.0f);
  // Create a transform object to perform rotational and positional transforms
  // on block objects.
  Transform transform;
  // Create a cube object of size 3x3x3.
  Cube cube(3);

  cube.SetRotation(X, 0, true);
  
  float counter = 0.0f;
  // Iterate over drawn frames.
  while (!display.IsClosed()) {
    display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
    
    // Change camera location.
    float sinCounter = sinf(counter);
    float cosCounter = cosf(counter);
    counter += 0.01f;
    camera.GetPos().x = 20 * sinCounter;
    camera.GetPos().z = 20 * cosCounter;
    camera.GetFor().x = -sinCounter;
    camera.GetFor().z = -cosCounter;
    
    // Continue any current cube animations.
    cube.UpdateRotation();

    cube.SetRotation(X, 0, true);
    
    cube.Draw(shader, transform, camera, blockMesh);

    display.Update();
  }
  return 0;
}
