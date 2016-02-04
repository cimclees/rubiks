/**
 * @file rubiks.cc
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the main function for a Rubik's Cube game.
 */

#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "../include/display.h"
#include "../include/mesh.h"
#include "../include/shader.h"
#include "../include/camera.h"
#include "../include/transform.h"
#include "../include/cube.h"

/**
 * Function to load settings from file "settings.conf"
 *
 * @param cubeSize The desired size of the cube (to be set).
 * @param winHeight The desired window height (to be set).
 * @param winWidth The desired window length (to be set).
 * @param mouseSens The desired mouse sensitivity (to be set).
 * @return True if loading is successful, otherwise false.
 */
bool LoadSettings(int& cubeSize, int& winHeight, 
                  int& winWidth, float& mouseSens);

/**
 * Function to process user input and carry out any indicated operations.
 *
 * @param quit To be set to true if user closes program window.
 * @param rightClick True when right mouse button is held down.
 * @camera Camera object to control perspective.
 * @cube Cube object on which to carry out indicated operations.
 * @param mouseSens Mouse sensitivity.
 */
void ProcessInput(bool& quit, bool& rightClick, Camera& camera, 
                  Cube& cube, float& mouseSens);

/**
 * Main function to run a Rubik's Cube game.
 */
int main() {
  // Load Settings.
  int cubeSize, winHeight, winWidth;
  float mouseSens;
  if (!LoadSettings(cubeSize, winHeight, winWidth, mouseSens)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Error",
                             "Failed to load settings form \"settings.conf\"",
                             NULL);
    return 1;
  }
  // Seed random number generator.
  srand(time(NULL));
  // Open a window.
  Display display(winWidth, winHeight, "Rubik's Cube");
  // Load 3D data for a block model.
  Mesh blockMesh("./data/model/block.obj");
  // Initialize shader.
  Shader shader("./data/shader/basicShader");
  // Create a camera object to manipulate positional perspective.
  Camera camera(70.0f, static_cast<float>(winWidth) / winHeight, 0.01f, 
                1000.0f, (cubeSize + 1.0f) * 3.0f);
  // Create a transform object to perform rotational and positional transforms
  // on block objects.
  Transform transform;
  // Create a cube object of desired size.
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

    ProcessInput(quit, rightClick, camera, cube, mouseSens);

    display.Update(quit);
  }
  return 0;
}

bool LoadSettings(int& cubeSize, int& winHeight, 
                  int& winWidth, float& mouseSens) {
  cubeSize = 0;
  winHeight = 0;
  winWidth = 0;
  mouseSens = 0.0f;
  
  std::ifstream settingsFile("settings.conf");
  std::string line;
  int lineNum = 1;
  if (settingsFile.is_open()) {
    try {
      while (std::getline(settingsFile, line)) {
        if (lineNum == 5) {
          cubeSize = stoi(line.substr(11));
        } else if (lineNum == 8) {
          winWidth = stoi(line.substr(14));
        } else if (lineNum == 9) {
          winHeight = stoi(line.substr(15));
        } else if (lineNum == 12) {
          mouseSens = stof(line.substr(13));
        }
        lineNum++;
      }
    } catch (std::exception& e) {
      cubeSize = 0; // Ensure function returns failure status.
    }
    settingsFile.close();
  }
  
  if (cubeSize > 0 && winHeight > 0 && winWidth > 0 && mouseSens > 0) {
    return true;
  } else {
    return false;
  }
}

void ProcessInput(bool& quit, bool& rightClick, Camera& camera, 
                  Cube& cube, float& mouseSens) {
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
          camera.GetHoriz() += (event.motion.xrel * -1 * mouseSens);
          if ((event.motion.yrel < 0 && sinf(camera.GetVert()) > (-PI / 4.0f)) ||
              (event.motion.yrel > 0 && sinf(camera.GetVert()) < (PI / 4.0f))) {
            camera.GetVert() += (event.motion.yrel * mouseSens);
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
