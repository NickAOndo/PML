/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Shader object header.
        -- Stores single shader (Vertex, Fragment), source & GPU id.
        -- Cleans up after itself.
        -- Future commits:  Add Geometry, Tessellation, and Compute.
*******************************************************************/


#ifndef PM_SHADER_H
#define PM_SHADER_H

#include <iostream> //STL
#include <string>
#include <GL/glew.h> // Middleware
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
namespace pm {

class Shader
{
public:
    Shader(GLenum shaderType);
    virtual ~Shader();
    Shader& operator=(const Shader& other);
    Shader(const Shader& other);

    void LoadShader(const char* fileName, std::string& shaderSource);
    void AttachShader(GLuint programID);
    void DetachShader(GLuint programID);
    void DeleteShader();
    bool Status();

protected:
private:
    std::string Type();

    GLuint shaderID;
    const GLenum shaderType;
    bool onGPU;
    bool status;
};

} // namespace pm

#endif // PM_SHADER_H
