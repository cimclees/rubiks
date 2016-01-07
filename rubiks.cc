/**
 * @file rubiks.cc
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the main function for a Rubik's Cube game.
 */

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "./display.h"
#include "./mesh.h"
#include "./shader.h"
#include "./camera.h"
#include "./transform.h"
#include "./cube.h"

// Window size
#define WIDTH 800
#define HEIGHT 600

// Mouse sensitivity
#define MOUSE_SENS 0.005f

/**
 * Function to process user input and carry out any indicated operations.
 *
 * @param quit To be set to true if user closes program window.
 * @param rightClick True when right mouse button is held down.
 * @camera Camera object to control perspective.
 * @cube Cube object on which to carry out indicated operations.
 */
void ProcessInput(bool& quit, bool& rightClick, Camera& camera, Cube& cube);

/**
 * Main function to run a Rubik's Cube game.
 */
int main() {
  int cubeSize = 5;
  // Seed random number generator.
  srand(time(NULL));
  // Open a window.
  Display display(WIDTH, HEIGHT, "Rubik's Cube");
  // Load 3D data for a block model.
  Mesh blockMesh("./res/block.obj");
  // Initialize shader.
  Shader shader("./res/basicShader");
  // Create a camera object to manipulate positional perspective.
  Camera camera(70.0f, static_cast<float>(WIDTH) / HEIGHT, 0.01f, 1000.0f,
                (cubeSize + 1.0f) * 3.0f);
  // Create a transform object to perform rotational and positional transforms
  // on block objects.
  Transform transform;
  // Create a cube object of size 3x3x3.
  Cube cube(cubeSize);
  

  bool quit       = false,  // True when the user has closed the window.
       rightClick = false;  // True when right mouse button is held down.
  // Iterate over drawn frames.
  while (!display.IsClosed()) {
    display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

    // Change camera position and orientation.
    camera.PositionCam();

    // Continue any current cube animations.
    cube.UpdateRotation();

    cube.Draw(shader, transform, camera, blockMesh);

    ProcessInput(quit, rightClick, camera, cube);

    display.Update(quit);
  }
  return 0;
}

void ProcessInput(bool& quit, bool& rightClick, Camera& camera, Cube& cube) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {  // Window closed.
        quit = true;
        break;
      }
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case (SDLK_r): {
            cube.SetRandRotation();
            break;
          }
          case (SDLK_PERIOD): {
            cube.SetRotation(Y, cube.GetSelected().y, true);
            break;
          }
          case (SDLK_COMMA): {
            cube.SetRotation(Y, cube.GetSelected().y, false);
            break;
          }
          case (SDLK_RIGHT): {
            cube.RotateXZ(Z, true, true, camera.GetFor());
            break;
          }
          case (SDLK_LEFT): {
            cube.RotateXZ(Z, false, false, camera.GetFor());
            break;
          }
          case (SDLK_UP): {
            cube.RotateXZ(X, true, false, camera.GetFor());
            break;
          }
          case (SDLK_DOWN): {
            cube.RotateXZ(X, false, true, camera.GetFor());
            break;
          }
        }
        break;
      }
      case SDL_MOUSEMOTION: {
        if (rightClick) {
          camera.GetHoriz() += (event.motion.xrel * -MOUSE_SENS);
          if ((event.motion.yrel < 0 && sinf(camera.GetVert()) > (-PI / 4.0f)) ||
              (event.motion.yrel > 0 && sinf(camera.GetVert()) < (PI / 4.0f))) {
            camera.GetVert() += (event.motion.yrel * MOUSE_SENS);
          }
        }
        break;
      }
      case SDL_MOUSEBUTTONDOWN: {
        if (event.button.button == SDL_BUTTON_RIGHT) {
          rightClick = true;
        } else if (event.button.button == SDL_BUTTON_LEFT) {
          glm::vec3 delta = camera.GetPickRay(event.button.x, event.button.y);
          cube.SelectBlock(camera.GetPos(), delta);
        }
        break;
      }
      case SDL_MOUSEBUTTONUP: {
        if (event.button.button == SDL_BUTTON_RIGHT) {
          rightClick = false;
        }
        break;
      }
    }
  }
}
