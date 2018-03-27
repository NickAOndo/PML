/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Shader object src.
        -- Stores single shader (Vertex, Fragment), source & GPU id.
        -- Cleans up after itself.
        -- Future commits:  Add Geometry, Tessellation, and Compute.
*******************************************************************/

#include "Shader.h"

#include <iostream> //STL
#include <string>
#include <fstream>
#include <GL/glew.h> // Middleware
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "PML/Renderer/ShaderCheckStatus.h" // PML
namespace pm {


Shader::Shader(GLenum shaderType)
: shaderID(0)
, shaderType(shaderType)
, onGPU(false)
, status(false)
{}

Shader::~Shader()
{
    DeleteShader();
}

Shader::Shader(const Shader& other)
:shaderID(0),
shaderType(other.shaderType),
onGPU(false),
status(false)
{}

std::string Shader::Type()
{
    if     (shaderType == GL_VERTEX_SHADER)     { return std::string("VS"); }
    else if(shaderType == GL_FRAGMENT_SHADER)   { return std::string("FS"); }
    else                                        { return std::string("??"); }
}


bool Shader::Status()
{
    return status;
}

void Shader::LoadShader(const char* fileName, std::string& shaderSource)
{
    std::string sourceFile = "assets/"+std::string(fileName)+"_"+Type()+".glsl";
    GetShaderSource(sourceFile.c_str(), shaderSource);
    const GLchar* pSource[1];
    pSource[0] = shaderSource.c_str();
    std::cout<<"Shader: Acquiring "<<sourceFile<<std::endl;

    shaderID = glCreateShader(shaderType);
    onGPU=true;
    glShaderSource(shaderID, 1, pSource, NULL);
    glCompileShader(shaderID);
    status = ShaderCheckStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);

    if(status)
        std::cout<<"Shader: Loaded "<<Type()<<" successfully."<<std::endl;
    else
        std::cout<<"Shader Error: Failed to load"<<Type()<<"!"<<std::endl;
}

void Shader::AttachShader(GLuint programID)
{
    if (status)
        glAttachShader(programID, shaderID);
    else
        std::cout<<"Shader: Shader not valid!"<<std::endl;
}

void Shader::DetachShader(GLuint programID)
{
    glDetachShader(programID, shaderID);
    std::cout<<"Detached "<<Type()<<" from program."<<std::endl;
}

void Shader::DeleteShader()
{
    if (onGPU)
    {
        glDeleteShader(shaderID);
        onGPU = false;
        status = false;
        std::cout<<"Shader: Deleted "<<Type()<<std::endl;
    }
}


// Utility function
void GetShaderSource(const char* fileName, std::string& shaderSource)
{
    shaderSource = "";
    std::ifstream fromFile;
    std::string currentLine;

    fromFile.open( fileName );
    if ( fromFile.is_open() )
    {
        while( getline( fromFile,  currentLine)  )
        {
            shaderSource += currentLine + "\n";
        }
    }
    else
    {
        printf("Error Shader: Can't read source file!");
    }

    fromFile.close();
}


} // namespace pm
