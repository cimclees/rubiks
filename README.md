# rubiks

This is a Rubik's Cube application I am developing to learn/practice the basics
of game programming using OpenGL, SDL, etc.

To Build on Linux:
  1. First install required packages:
    * libsdl2-dev
    * libglew-dev
    * libglm-dev
  
  2. Run 'make' from the main project directory ('rubiks')
  
  3. The game will be built and saved as an executable named 'rubiks' in the
     main project directory.

Settings:
  * Adjust cube size, window dimensions, and mouse sensitivity in the
    'settings.conf' file in the main project directory ('rubiks')

Controls:
  * Hold right click and move mouse to adjust view.
  * Click to select a block to rotate.
  * Click off the cube to unselect a block.
  * Use comma, period, and arrow keys to perform rotations.
  * Use the 'r' key to perform a random rotation.

Much of the OpenGL code is adapted from a tutorial made by 'thebennybox': 
https://www.youtube.com/channel/UCnlpv-hhcsAtEHKR2y2fW4Q

The OBJ loading functionality implemented in obj_loader.cc and obj_loader.h is
taken directly from sample code associated with the same tutorial:
https://github.com/BennyQBD/ModernOpenGLTutorial

Image loading is handled by the stb_image API:
https://github.com/nothings/stb
