/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Stage object file.
*******************************************************************/

#include "PML/Stage/Stage.h"
#include <vector> //STL
#include <memory>
#include <iostream>
#include "PML/PhaseRelay.h" // PML
#include "PML/Renderer/Mesh.h"
#include "PML/Stage/StageActor.h"
namespace pm{

Stage::Stage()
: actors()
, pVertices( std::make_shared<std::vector<Vertex>>() )
, pIndices ( std::make_shared<std::vector<Element>>() )
, actorMesh( std::make_shared<Mesh<Vertex,Element>>(pVertices, pIndices) )
{
    std::cout<<"Stage: created."<<std::endl;
}


Stage::~Stage()
{
    std::cout<<"Stage destroyed."<<std::endl;
}


Stage::Stage(const Stage& other)
: actors()
, pVertices( std::make_shared<std::vector<Vertex>>() )
, pIndices ( std::make_shared<std::vector<Element>>() )
, actorMesh( std::make_shared<Mesh<Vertex,Element>>(pVertices, pIndices))
{
    std::cout<<"Stage: Mesh pVertex="<<pVertices.get()<<", pIndices="<<pIndices.get()<<std::endl;
}


void Stage::AddStageActor(vec3& nPos, GLfloat& w, GLfloat& h)
{
    GLushort objID = (GLushort) actors.size();
    std::cout<<"Stage: "<<objID<<"=0"<<std::endl; //Check index is correct
	actors.push_back(std::make_shared<StageActor>(nPos, w, h, objID) );

    pIndices->reserve(6);
    pIndices->push_back( Element(6*objID+0) );
    pIndices->push_back( Element(6*objID+1) );
    pIndices->push_back( Element(6*objID+2) ); // Tri: UL->UR->DR
    pIndices->push_back( Element(6*objID+2) );
    pIndices->push_back( Element(6*objID+3) );
    pIndices->push_back( Element(6*objID+0) ); // Tri: DR->DL->UL

    pVertices->reserve(4);
                         //     POSITION                 COLOR                    NORMAL                   TEXCOORD
    pVertices->push_back(Vertex(vec3(+0.5f,-0.5f,+0.0f), vec3(+1.0f,+1.0f,+1.0f), vec3(+0.0f,+0.0f,-1.0f), vec2(+0.0f,+0.0f) )); // UL
    pVertices->push_back(Vertex(vec3(+0.5f,+0.5f,+0.0f), vec3(+1.0f,+1.0f,+1.0f), vec3(+0.0f,+0.0f,-1.0f), vec2(+1.0f,+0.0f) )); // UR
    pVertices->push_back(Vertex(vec3(-0.5f,-0.5f,+0.0f), vec3(+1.0f,+1.0f,+1.0f), vec3(+0.0f,+0.0f,-1.0f), vec2(+1.0f,+1.0f) )); // DR
    pVertices->push_back(Vertex(vec3(-0.5f,-0.5f,+0.0f), vec3(+1.0f,+1.0f,+1.0f), vec3(+0.0f,+0.0f,-1.0f), vec2(+0.0f,+1.0f) )); // DL

    actorMesh->GenerateMesh();
}


void Stage::UpdateStage( pm::PhaseRelay& phRelay )
{
    for( GLuint i=0; i<actors.size(); ++i )
    {
        // Update Actors
        actors[i]->UpdateActor(phRelay);
        GLfloat w = actors[i]->w;
        GLfloat h = actors[i]->h;
        vec3 nPos = actors[i]->position;
        // Update their screen positions
        (*pVertices.get())[i+0].position = nPos;
        (*pVertices.get())[i+1].position = nPos+vec3(   +w, +0.0f, +0.0f);
        (*pVertices.get())[i+2].position = nPos+vec3(   +w,    -h, +0.0f);
        (*pVertices.get())[i+3].position = nPos+vec3(+0.0f,    -h, +0.0f);
    }
}


void Stage::DrawActors()
{
    actorMesh->Bind();
    actorMesh->UpdateMesh();
    actorMesh->RenderMesh();
    actorMesh->Unbind();
}


} // end namespace
