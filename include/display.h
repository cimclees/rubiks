/**
 * @file display.h
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the declerations of a class to manage a window using
 * SDL which will render a 3D environment using OpenGL.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>

class Display {

  public:
    /**
     * Constructor for a display object.
     *
     * @param width Desired window width.
     * @param height Desired window height.
     * @param title Desired window title.
     */
    Display(int width, int height, const std::string& title);

    /**
     * Overwrite entire window with a single color.
     * @param r Red color value.
     * @param g Green color value.
     * @param b Blue color value.
     * @param a Alpha value.
     */
    void Clear(float r, float g, float b, float a);
    
    /**
     * Update display with next rendered frame from OpenGL.
     *
     * @param quit True to close window.
     */
    void Update(bool quit);

    /**
     * Check if a display is closed.
     *
     * @return True if the display is closed, otherwise false.
     */
    bool IsClosed();
    
    /**
     * Display descructor.
     */
    ~Display();
  protected:
  private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    bool m_isClosed;
};

#endif // DISPLAY_H
