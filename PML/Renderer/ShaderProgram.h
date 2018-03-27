/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: ShaderProgram header.
        -- Container and manager for:
            a.) shader program GPU id
            b.) individual Shader instances (Vertex, Fragment)
            c.) associated loading, deleting, using utils.
*******************************************************************/

#ifndef PM_SHADERPROGRAM_H
#define PM_SHADERPROGRAM_H

#include <iostream> //STL
#include <string>
#include <vector>
#include <memory>
#include <GL/glew.h> // Middleware
#include "PML/Renderer/Shader.h" // PML
#include "PML/Renderer/ShaderCheckStatus.h"
namespace pm {


class ShaderProgramAdapter
{
public:
    ShaderProgramAdapter();
    virtual ~ShaderProgramAdapter();
    ShaderProgramAdapter(const ShaderProgramAdapter& other);

    void UseProgram();
    void LoadProgram(const char* file_Name);
    void DeleteProgram();
    virtual void BindVertexAttribs()=0;

    GLuint programID;

protected:
private:
    ShaderProgramAdapter& operator=(const ShaderProgramAdapter& other);

    //static const GLuint NUM_SHADERS=2;
    std::vector<pm::Shader> shaders;
    bool onGPU;
    bool status;
};


template <class V>
class ShaderProgram : public ShaderProgramAdapter
{
public:
    ShaderProgram();
    virtual ~ShaderProgram();
    ShaderProgram(const ShaderProgram& other);

    void BindVertexAttribs();

protected:
private:
    ShaderProgram& operator=(const ShaderProgram& other);
};

// IMPLEMENTATION OF CLASS "ShaderProgram<V>"

template <class V>
ShaderProgram<V>::ShaderProgram()
{}


template <class V>
ShaderProgram<V>::ShaderProgram(const ShaderProgram& other)
{}


template <class V>
ShaderProgram<V>::~ShaderProgram()
{}


/*
    N.B. The Mesh forces the Vertex data's location,
    so we force the ShaderProgram to respect this.
    (This isn't an issue for GLSL >4, where this
    can be specific directly in GLSL.
*/
template <class V>
void ShaderProgram<V>::BindVertexAttribs()
{
    for(GLint i=0; i<<V::NUM_ATTRIBS; ++i)
        glBindAttribLocation(this->programID, i, V::ATTRIB_NAMES[i]);
}


} // namespace pm
#endif // PM_SHADERPROGRAM_H
