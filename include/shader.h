/**
 * @file shader.h
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the declerations of an OpenGL shader.
 */

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "./transform.h"
#include "./camera.h"

class Shader {
  public:
    /**
     * Constructor for a shader.
     *
     * @param filename Filename for vertex shader and fragment shader, to be
     *    appended with ".vs" and ".fs" respectively, and loaded from
     *    "../data/shader".
     */
    Shader(const std::string& filename);

    /**
     * Activate a shader to be used in a mesh rendering.
     */
    void Bind();

    /**
     * Update a shader to reflect transforms applied to a mesh and camera
     *    angle and position.
     *
     * @param transform Transforms applied to an object to be shaded.
     * @param camera Active camera object.
     */
    void Update(const Transform& transform, const Camera& camera);

    /**
     * Descructor for a shader object. Unload shader from graphics card
     *    via OpenGL.
     */
    ~Shader();
  protected:
  private:
    static const unsigned int NUM_SHADERS = 2;

    /**
     * @enum Shader program parameters.
     */
    enum {
      TRANSFORM_U,

      NUM_UNIFORMS
    };

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
};

#endif  // SHADER_H
