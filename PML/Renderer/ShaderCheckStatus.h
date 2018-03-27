/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: ShaderProgram error-checking utility header.
*******************************************************************/

#ifndef PM_SHADERCHECKSTATUS_H
#define PM_SHADERCHECKSTATUS_H

#include <string> //STL
#include <GL/glew.h> // Middleware
namespace pm{


bool ShaderCheckStatus(GLuint objID,
                     PFNGLGETSHADERIVPROC objGetPropertyFunc,
                     PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
                     GLenum statusType);

void GetShaderSource(const char* fileName, std::string& shaderSource);


} // namespace pm
#endif // SHADERCHECKSTATUS_H_INCLUDED


