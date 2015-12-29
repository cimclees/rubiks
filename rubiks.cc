/**
 * @file rubiks.cc
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the main function for a Rubik's Cube game.
 */

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "transform.h"
#include "cube.h"

// Window size
#define WIDTH 800
#define HEIGHT 600

#define MOUSE_SENS 0.005f

/**
 * Function to position and orient a camera.
 *
 * @param position Camera postion vector to be set.
 * @param forward Camera forward vector to be set.
 * @param horizOffset Value used to compute position on x and z axes.
 * @param vertOffset  Value used to compuet position on y axis.
 */
void positionCam(glm::vec3& position, glm::vec3& forward,
                 const float& horizOffset, const float& vertOffset) {
    float sinHoriz = sinf(horizOffset);
    float cosHoriz = cosf(horizOffset);
    position.x = 20 * sinHoriz;
    position.z = 20 * cosHoriz;
    forward.x = -sinHoriz;
    forward.z = -cosHoriz;
    
    float sinVert = sinf(vertOffset);
    position.y = 20 * sinVert;
    forward.y = -sinVert;
}

/**
 * Function to choose correct rotation to make on X or Z axes depending on
 * camera orientation and carry out that rotation.
 *
 * @param absZgreaterX The dimension of rotation to be used when the absolute
 *   value of the z component of the forward vector of the camera is greater
 *   than the absolute value of the x component of the camera's forward vector.
 * @param ZgreatX True if rotation to be clockwise when the value of
 *   the z component of the forward vector of the camera is greater than the 
 *   absolute value of the x component of the camera's forward vector.
 * @param XgreatZ True if rotation to be clockwise when the value of
 *   the x component of the forward vector of the camera is greater than the 
 *   absolute value of the z component of the camera's forward vector.
 * @param camera Camera object used to determine proper roation.
 * @param cube Cube on which to make rotation.
 */
void RotateXZ(Dim absZgreaterX, bool ZgreatX, bool XgreatZ, 
              Camera& camera, Cube& cube) {
  Dim absXgreaterZ;
  int absZgreaterXn;
  int absXgreaterZn;

  if (absZgreaterX == Z) {
    absZgreaterXn = cube.GetSelected().z;
    absXgreaterZ = X;
    absXgreaterZn = cube.GetSelected().x;
  } else {
    absZgreaterXn = cube.GetSelected().x;
    absXgreaterZ = Z;
    absXgreaterZn = cube.GetSelected().z;
  }

  if (camera.GetFor().z > fabs(camera.GetFor().x)) {
    cube.SetRotation(absZgreaterX, absZgreaterXn, ZgreatX); 
  } else if (camera.GetFor().z < -1.0f * fabs(camera.GetFor().x)) {
    cube.SetRotation(absZgreaterX, absZgreaterXn, !ZgreatX);
  } else if (camera.GetFor().x > fabs(camera.GetFor().z)) {
    cube.SetRotation(absXgreaterZ, absXgreaterZn, XgreatZ);
  } else if (camera.GetFor().x < -1.0f * fabs(camera.GetFor().z)) {
    cube.SetRotation(absXgreaterZ, absXgreaterZn, !XgreatZ);
  }
}

/**
 * Main function to run a Rubik's Cube game.
 */
int main() {
  srand(time(NULL));
  // Open a window.
  Display display(WIDTH, HEIGHT, "Rubik's Cube");
  // Load 3D data for a block model.
  Mesh blockMesh("./res/block.obj");
  // Initialize shader.
  Shader shader("./res/basicShader");
  // Create a camera object to manipulate positional perspective.
  float horizOffset = 0.0f;
  float vertOffset  = 0.0f;
  Camera camera(glm::vec3(0,0,0), 70.0f, ((float) WIDTH) / HEIGHT, 
                0.01f, 1000.0f);

  // Create a transform object to perform rotational and positional transforms
  // on block objects.
  Transform transform;
  // Create a cube object of size 3x3x3.
  Cube cube(3);

  bool quit = false;
  bool rightClick = false;
  // Iterate over drawn frames.
  while (!display.IsClosed()) {
    display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
    
    // Change camera position and orientation.
    positionCam(camera.GetPos(), camera.GetFor(), horizOffset, vertOffset);

    // Continue any current cube animations.
    cube.UpdateRotation();

    cube.Draw(shader, transform, camera, blockMesh);

    // Process user input.
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
              RotateXZ(Z, true, true, camera, cube);
              break;
            }
            case (SDLK_LEFT): {
              RotateXZ(Z, false, false, camera, cube);
              break;
            }
            case (SDLK_UP): {
              RotateXZ(X, true, false, camera, cube);
              break;
            }
            case (SDLK_DOWN): {
              RotateXZ(X, false, true, camera, cube);
              break;
            }
          }
          break;
        }
        case SDL_MOUSEMOTION: {
          if (rightClick) {
            horizOffset += (event.motion.xrel * -MOUSE_SENS);
            if ((event.motion.yrel < 0 && sinf(vertOffset) > (-PI / 4.0f)) ||
                (event.motion.yrel > 0 && sinf(vertOffset) < (PI / 4.0f))) {
              vertOffset  += (event.motion.yrel * MOUSE_SENS);
            }
          }
          break;
        }
        case SDL_MOUSEBUTTONDOWN: {
          if (event.button.button == SDL_BUTTON_RIGHT) {
            rightClick = true;
          } else if (event.button.button == SDL_BUTTON_LEFT) {
            
            glm::vec3 rayStart;
            glm::vec3 rayEnd;

            camera.GetPickRay(event.button.x, event.button.y, rayStart, rayEnd);
            
            // Ray Collision Check
            glm::vec3 currPoint(rayStart);
            bool found = false;
          
            glm::vec3 delta = normalize(rayEnd - rayStart) / 100.0f; 
            
            int x = 0;
            int y = 0;
            int z = 0;

            // Get close to cube
            while (fabs(currPoint.x) > 3.1f &&
                   fabs(currPoint.y) > 3.1f &&
                   fabs(currPoint.z) > 3.1f) {
              currPoint.x += delta.x;
              currPoint.y += delta.y;
              currPoint.z += delta.z;
            }

            while (!found && (fabs(currPoint.x) < 3.2f
                              ||  fabs(currPoint.y) < 3.2f
                              ||  fabs(currPoint.z) < 3.2f)) {

              currPoint.x += delta.x;
              currPoint.y += delta.y;
              currPoint.z += delta.z;

              for (x = 0; x < 3 && !found; x++) {
                for (y = 0; y < 3 && !found; y++) {
                  for (z = 0; z < 3 && !found; z++) {
                      if (fabs(cube.GetPos(x, y, z).x - currPoint.x) < 1.0f
                        && fabs(cube.GetPos(x, y, z).y - currPoint.y) < 1.0f
                        && fabs(cube.GetPos(x, y, z).z - currPoint.z) < 1.0f) {
                      found = true;
                      cube.GetSelected() = glm::vec3(x, y, z);
                    }
                  }
                }
              }  
            }

            if (!found) {
              cube.GetSelected() = glm::vec3(-1, -1, -1);
            }
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
    display.Update(quit);
  }
  return 0;
}
