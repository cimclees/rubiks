/**
 * @file display.cc
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the implementation of a class to manage a window using
 * SDL which will render a 3D environment using OpenGL.
 */

#include <iostream>
#include <GL/glew.h>
#include "../include/display.h"

Display::Display(int width, int height, const std::string& title) {
  SDL_Init(SDL_INIT_EVERYTHING);

  // Set up buffers
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // Antialiasing
  // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

  m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_OPENGL);
  m_glContext = SDL_GL_CreateContext(m_window);

  GLenum status = glewInit();

  if (status != GLEW_OK) {
    std::cerr << "Glew failed to intitialize!" << std::endl;
  }

  m_isClosed = false;

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_MULTISAMPLE);
}

void Display::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsClosed() {
  return m_isClosed;
}

void Display::Update(bool quit) {
  SDL_GL_SwapWindow(m_window);
  if (quit) {
    m_isClosed = true;
  }
}

Display::~Display() {
  SDL_GL_DeleteContext(m_glContext);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}
