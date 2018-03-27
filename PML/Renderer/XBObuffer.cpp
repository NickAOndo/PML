/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: XBObuffer class header.
        -- N.B. Example instance of a template-arg type for use
           with Mesh and MeshXBO templates.
        -- Instances include Vertex, Element, & Transform classes.
*******************************************************************/


#include "PML/Renderer/XBObuffer.h"

#include <glm/glm.hpp> // Middleware
#include <GL/glew.h>

namespace pm{

GLfloat ar = 1360.0f/768.0f; // aspect ratio

Vertex::Vertex(vec3 position, vec3 color, vec3 normal, vec2 texCoord )
: position(position)
, color(color)
, normal(normal)
, texCoord(texCoord)
{}

const GLint Vertex::ATTRIB_FORMAT[] = { 3, 3, 3,  2};
const GLchar* Vertex::ATTRIB_NAMES[] = {"position", "color", "normal", "texCoord"};


Element::Element( GLuint index)
:index((GLushort) index)
{}

/*
Transform::Transform(mat4 transformation)
:transformation(transformation)
{}
*/

} // pm namespace
