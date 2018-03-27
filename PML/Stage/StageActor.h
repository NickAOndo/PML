/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: StageActor header file for class.
*******************************************************************/

#ifndef PM_STAGEACTOR_H
#define PM_STAGEACTOR_H

#include "PML/PhaseRelay.h"
#include "PML/Renderer/XBObuffer.h"
#include <string>
namespace pm{

class StageActor
{
public:
    StageActor( vec3& position, GLfloat& width, GLfloat& height, GLushort actorID);
    virtual ~StageActor();
    StageActor(const StageActor& other);
    //StageActor& operator=( const StageActor& other );

    void UpdateActor( pm::PhaseRelay& phRelay );

    vec3 position;
    GLfloat w;
    GLfloat h;
    GLushort actorID;
protected:
private:
};

}
#endif // STAGEACTOR_H
