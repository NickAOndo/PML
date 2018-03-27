/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Stage class header.
*******************************************************************/

#ifndef PM_Stage_H
#define PM_Stage_H

#include <vector> //STL
#include <memory>
#include "PML/PhaseRelay.h" // PML
#include "PML/Renderer/Mesh.h"
#include "PML/Stage/StageActor.h"
namespace pm{

class Stage
{
public:
	Stage();
	~Stage();
	Stage(const Stage& other);

    void AddStageActor( vec3& nPos, GLfloat& w, GLfloat& h );
	void UpdateStage( pm::PhaseRelay& phRelay );
	void DrawActors();

protected:
private:
	Stage& operator=(const Stage& other);

    std::vector<std::shared_ptr<pm::StageActor>> actors;
    std::shared_ptr<std::vector<Vertex>> pVertices;
    std::shared_ptr<std::vector<Element>> pIndices;
    std::shared_ptr<Mesh<Vertex,Element>> actorMesh;

};

}
#endif // Stage_H
