/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: StageActor class object file.
*******************************************************************/

#include "StageActor.h"
#include "PML/PhaseRelay.h"
#include <string>
#include <iostream>
#include <math.h>
namespace pm{

StageActor::StageActor( vec3& position, GLfloat& width, GLfloat& height, GLushort actorID)
:position(position)
,w(width)
,h(height)
,actorID(actorID)
{}

StageActor::~StageActor()
{}

StageActor::StageActor(const StageActor& other)
:position(other.position)
,w(other.w)
,h(other.h)
,actorID(other.actorID)
{}


void StageActor::UpdateActor( pm::PhaseRelay& phRelay)
{
    GLfloat t = phRelay.frames/ 59.0f;
    GLfloat dx = (GLfloat) 0.4f*cosf( t*1.5f);
    GLfloat dy = (GLfloat) 0.4f*sinf( t*1.5f);
    GLfloat dz = (GLfloat) 0.5f*sinf(t*2.5f);
    position = vec3(-0.5f+dx, +0.5f+dy, +0.0f+dz);
}

} // end namespace
