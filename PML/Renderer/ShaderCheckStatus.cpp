/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: ShaderProgram error-checking utility src.
*******************************************************************/


#include "PML/Renderer/ShaderCheckStatus.h"

#include <iostream> // STL
#include <GL/glew.h> // Middleware
namespace pm{

bool ShaderCheckStatus(GLuint objID,
                     PFNGLGETSHADERIVPROC objGetPropertyFunc,
                     PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
                     GLenum statusType)
{
    GLint status;
    objGetPropertyFunc(objID, statusType, &status);
    if( status != GL_TRUE )
    {
        GLint infoLogLength;
        objGetPropertyFunc(objID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* errorMessage = new GLchar[infoLogLength];
        GLsizei messageSize;
        getInfoLogFunc(objID, infoLogLength, &messageSize, errorMessage);
        std::cout<<"ShaderProgram Error: GLSL: "<<errorMessage<<std::endl;
        delete [] errorMessage;
        return false;
    }
    return true;
}


} // pm namespace
