/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: ShaderProgram src.
        -- Container and manager for:
            a.) shader program GPU id
            b.) individual Shader instances (Vertex, Fragment)
            c.) associated loading, deleting, using utils.
*******************************************************************/

#include "PML/Renderer/ShaderProgram.h"

#include "PML/Renderer/XBObuffer.h"

#include <iostream> //STL
#include <string>
#include <string>
#include <GL/glew.h> // Middleware
#include "PML/Renderer/Shader.h"
#include "PML/Renderer/ShaderCheckStatus.h"
namespace pm {


ShaderProgramAdapter::ShaderProgramAdapter()
: programID(0)
, shaders()
, onGPU(false)
, status(false)
{
}


ShaderProgramAdapter::ShaderProgramAdapter(const ShaderProgramAdapter& other)
: programID(0)
, shaders()
, onGPU(false)
, status(false)
{
}


ShaderProgramAdapter::~ShaderProgramAdapter()
{
    DeleteProgram();
}


void ShaderProgramAdapter::UseProgram()
{
    // Bind
    if( status )
        glUseProgram(programID);
    else
        std::cout<<"Error ShaderProgram: Program not valid!"<<std::endl;
}


void ShaderProgramAdapter::LoadProgram( const char* fileName )
{
    programID = glCreateProgram();
    onGPU = true;

    shaders.push_back( Shader(GL_VERTEX_SHADER) );
    shaders.push_back( Shader(GL_FRAGMENT_SHADER) );

    std::string shaderSource;
    for(GLuint i=0; i<shaders.size(); i++)
    {
        shaders[i].LoadShader(fileName, shaderSource);
        shaders[i].AttachShader(programID);
    }

    BindVertexAttribs();
    glBindFragDataLocation(programID, 0, "outColor");
    glLinkProgram(programID);

    if( ShaderCheckStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS) )
    {
        glValidateProgram(programID);
        status = ShaderCheckStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_VALIDATE_STATUS);
    }
}

void ShaderProgramAdapter::DeleteProgram()
{
    if( onGPU )
    {
        for (GLuint i=0; i<shaders.size(); i++)
        {
            shaders[i].DetachShader(programID);
        }
        glDeleteProgram(programID);
        std::cout<<"ShaderProgram: Deleted."<<std::endl;
    }
    onGPU=false;
}

} // namespace pm
