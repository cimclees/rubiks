/**
 * @file shader.cc
 * @author Charles Ian Mclees
 *  
 * @section DESCRIPTION
 *
 * This file contains the implementation of an OpenGL shader.
 */

#include <fstream>
#include <iostream>
#include "../include/shader.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram,
                             const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName) {
  m_program = glCreateProgram();
  // Vertex Shader
  m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
  // Fragment Shader
  m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

  for (unsigned int i = 0; i < NUM_SHADERS; i++) {
    glAttachShader(m_program, m_shaders[i]);
  }

  glBindAttribLocation(m_program, 0, "position");
  glBindAttribLocation(m_program, 1, "texCoord");
  glBindAttribLocation(m_program, 2, "normal");

  glLinkProgram(m_program);
  CheckShaderError(m_program, GL_LINK_STATUS, true,
                   "Error: Program linking failed: ");
  glValidateProgram(m_program);
  CheckShaderError(m_program, GL_VALIDATE_STATUS, true,
                   "Error: Program is invalid: ");

  m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

void Shader::Bind() {
  glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera) {
  glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
  glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

Shader::~Shader() {
  for (unsigned int i = 0; i < NUM_SHADERS; i++) {
    glDetachShader(m_program, m_shaders[i]);
    glDeleteShader(m_shaders[i]);
  }
  glDeleteProgram(m_program);
}

/**** Shader intialization functions below. ****/

/**
 * Intialize a shader in OpenGL.
 *
 * @param text Code for shader program.
 * @param shaderType Shader type (vertex or fragment)
 * @return The index of the new shader.
 */
static GLuint CreateShader(const std::string& text, GLenum shaderType) {
  GLuint shader = glCreateShader(shaderType);

  if (shader == 0) {
    std::cerr << "Error: Shader creation failed!" << std::endl;
  }

  const GLchar* shaderSourceStrings[1];
  GLint shaderSourceStringLengths[1];

  shaderSourceStrings[0] = text.c_str();
  shaderSourceStringLengths[0] = text.length();

  glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
  glCompileShader(shader);

  CheckShaderError(shader, GL_COMPILE_STATUS, false,
                   "Error: Shader compilation failed: ");

  return shader;
}

/**
 * Load text of a shader program.
 *
 * @param fileName the shader program to load.
 * @return the text of the specified file.
 */
static std::string LoadShader(const std::string& fileName) {
  std::ifstream file;
  file.open((fileName).c_str());

  std::string output;
  std::string line;

  if (file.is_open()) {
    while (file.good()) {
      getline(file, line);
      output.append(line + "\n");
    }
  } else {
    std::cerr << "Unable to load shader: " << fileName << std::endl;
  }

  return output;
}

/**
 * Ensure shader loaded successfully.
 *
 * @param shader The index of the shader to be checked.
 * @param flag Property to check.
 * @param isProgram True to check program, false for shader.
 * @param errorMessage Output message if check fails.
 */
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram,
                             const std::string& errorMessage) {
  GLint success = 0;
  GLchar error[1024] = { 0 };

  if (isProgram) {
    glGetProgramiv(shader, flag, &success);
  } else {
    glGetShaderiv(shader, flag, &success);
  }

  if (success == GL_FALSE) {
    if (isProgram) {
      glGetProgramInfoLog(shader, sizeof(error), NULL, error);
    } else {
      glGetShaderInfoLog(shader, sizeof(error), NULL, error);
    }

    std::cerr << errorMessage << ": '" << error << "'" << std::endl;
  }
}
