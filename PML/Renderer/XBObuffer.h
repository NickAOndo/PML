/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: XBObuffer class header.
        -- N.B. Example instance of a template-arg type for use
           with Mesh and MeshXBO templates.
        -- Instances include Vertex, Element, & Transform classes.
*******************************************************************/

#ifndef PM_XBOBUFFER_H
#define PM_XBOBUFFER_H

#include <math.h>
#include <glm/glm.hpp>  // Middleware
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "PML/PhaseRelay.h"
namespace pm {

extern GLfloat ar;

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat4 = glm::mat4;
///////////////////////////////////////////////
////////// VERTEX DATA TYPES //////////////////
class Element
{
public:
    //Element(GLushort index);
    Element(GLuint index);
    GLushort index;

    static const GLenum DATA_TYPE = GL_UNSIGNED_SHORT;
};


class Vertex
{
public:
    Vertex(vec3 pos, vec3 color, vec3 normal, vec2 texCoord );
    void VertexAttribPointer();

    vec3 position;
    vec3 color;
    vec3 normal;
    vec2 texCoord;
    static const GLint NUM_ATTRIBS = 4;
    static const GLint ATTRIB_FORMAT[NUM_ATTRIBS];
    static const GLchar* ATTRIB_NAMES[NUM_ATTRIBS];
    static const GLenum PRIMITIVE_TYPE = GL_FLOAT;
    static const GLuint PRIMITIVE_SIZE = sizeof(GLfloat);
};

/////////////////////////////////////////////////
///////////////  UNIFORMS  //////////////////////
class Transform
{
public:
    Transform( const vec3& position, GLfloat fov, GLfloat aspect, GLfloat zNear, GLfloat zFar)
        : m_perspective( mat4(1.0f) )
        , m_view(mat4(1.0f))
        , m_position(position)
        , m_forward( vec3(0.0f,0.0f,1.0f) )
        , m_up( vec3(0.0f,1.0f,0.0f) )
    {
        m_perspective = glm::perspective(fov, aspect, zNear, zFar);
        m_view = glm::lookAt(m_position, m_position+m_forward, m_up );
    }

    inline void UpdateUniform(GLuint programID, PhaseRelay& phRelay)
    {
        vec3 trans = vec3(0.0f, 0.0f, 0.0f);
        GLfloat t = phRelay.frames / 59.5f;
        vec3 rot = vec3(45.0f*cosf(2.0f*t), 45.0f*sinf(2.0f*t), 20.0f*sinf(2.0f));
        vec3 rescale = vec3(ar, 1.0f, 1.0f); //fix aspect

        mat4 trans_Model = glm::translate(mat4(1.0f), trans);
        mat4 rotZ_Model  = glm::rotate(mat4(1.0f), rot.z, vec3(1.0f, 0.0f, 0.0f) );
        mat4 rotY_Model  = glm::rotate(mat4(1.0f), rot.y, vec3(0.0f, 1.0f, 0.0f) );
        mat4 rotX_Model  = glm::rotate(mat4(1.0f), rot.x, vec3(0.0f, 0.0f, 1.0f) );
        mat4 scale_Model = glm::scale(glm::mat4(1.0f), rescale);
        mat4 model = trans_Model*rotZ_Model*rotY_Model*rotX_Model*scale_Model;

        model = m_perspective*m_view*model;
        GLint location = glGetUniformLocation(programID, "transform");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));
    }

    //mat4 transformation;
private:
    mat4 m_perspective;
    mat4 m_view;
    vec3 m_position;
    vec3 m_forward;
    vec3 m_up;
};

} // namespace pm
#endif // PM_XBOBUFFER_H
