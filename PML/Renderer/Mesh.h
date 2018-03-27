/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description:  Template Mesh class.
        - Loads and manipulates custom-data meshes on GPU.
        - Uses and manages MeshXBO objects for VBO and EBO.
*******************************************************************/

#ifndef PM_MESH_H
#define PM_MESH_H

#include <vector>
#include <memory>
#include <glm/glm.hpp> // Middleware
#include <GL/glew.h>
#include "PML/Renderer/MeshXBO.h"

/*
    RE-FACTOR CODE:
        1.) Return to the old convention, of only loading bufferArray -> buffers in the GenerateBuffers call
        2.) Modify UpdateBuffers as is necessary.
*/

/*
//////////////////////////////////////////////////////////
    * This is an adapter for Mesh templated classes
    * Allows them to be stored in a unified memory manager
*/
namespace pm {

class MeshAdapter
{
public:
    MeshAdapter();
    virtual ~MeshAdapter();
    MeshAdapter(const MeshAdapter& other);

    virtual void GenerateMesh()=0;
    virtual void UpdateMesh()=0;
    virtual void Delete()=0;
    virtual void RenderMesh()=0;
    virtual void Bind()=0;
    virtual void Unbind()=0;
};

////////////////////////////////////////////////////
//// A KIND OF Mesh TEMPLATED CLASS
//  This is designed to work with


template<class V, class E>
class Mesh : public MeshAdapter
{
public:
    Mesh( std::shared_ptr<std::vector<V>> pVertices,
          std::shared_ptr<std::vector<E>> pElements);
    ~Mesh();
    Mesh(const Mesh& other);

    void GenerateMesh();
    void UpdateMesh();
    void Delete();
    void RenderMesh();
    void Bind();
    void Unbind();

private:
    Mesh& operator=(const Mesh& other);
    void SetAttribPointers();

    bool onGPU;
    GLuint vaoID;
    MeshXBO<V> vbo;
    MeshXBO<E> ebo;
};

// IMPLEMENTATION OF TEMPLATE

template<class V, class E>
Mesh<V,E>::Mesh( std::shared_ptr<std::vector<V>> pVertices,
                 std::shared_ptr<std::vector<E>> pElements)
: onGPU(false)
, vaoID(0)
, vbo( pVertices, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW )
, ebo( pElements, GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW )
{}

template<class V, class E>
Mesh<V,E>::Mesh(const Mesh& other)
:onGPU(false)
, vaoID(0)
, vbo(other.vbo)
, ebo(other.ebo)
{}

template<class V, class E>
Mesh<V,E>::~Mesh()
{
    Delete();
    vaoID=0;
}

template<class V, class E>
void Mesh<V,E>::GenerateMesh()
{
    std::cout<<"Mesh generating: pVertex="<<vbo.pBuffers.get()<<", pIndices="<<ebo.pBuffers.get()<<std::endl;
    std::cout<<"Size: pVertex="<<vbo.pBuffers->size()<<", pIndices="<<ebo.pBuffers->size()<<std::endl;
    glGenVertexArrays(1, &vaoID);
    Bind();
        if( vbo.pBuffers->size() == 0 )
        {
            std::cout<<"Error Mesh: Can't load empty VBO!"<<std::endl;
            glDeleteVertexArrays(1, &vaoID);
        }
        else
        {
            if( ebo.pBuffers->size() == 0  )
            {
                std::cout<<"Error Mesh: Can't load empty EBO!"<<std::endl;
                glDeleteVertexArrays(1, &vaoID);
            }
            else
            {
                vbo.GenerateBuffers();
                ebo.GenerateBuffers();
                SetAttribPointers();

                onGPU=true;
                std::cout<<"Mesh: Generated!"<<std::endl;
            }
        }
    Unbind();
}

template<class V, class E>
void Mesh<V,E>::SetAttribPointers()
{
    GLuint stride=0;

    for( GLint i=0; i<V::NUM_ATTRIBS; ++i )
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, V::ATTRIB_FORMAT[i], V::PRIMITIVE_TYPE, GL_FALSE, sizeof(V), (void*) (stride) );
        stride +=  V::ATTRIB_FORMAT[i] * V::PRIMITIVE_SIZE;
    }
}


template<class V, class E>
void Mesh<V,E>::UpdateMesh()
{
    if(onGPU)
    {
        vbo.UpdateBuffers();
        ebo.UpdateBuffers();
    }
    else
        std::cout<<"Error Mesh: Can't load VBO/EBO, no GPU access!"<<std::endl;
}


template<class V, class E>
void Mesh<V,E>::Delete()
{
    if(onGPU)
    {
        Bind();
            ebo.Delete();
            vbo.Delete();
            glDeleteVertexArrays(1, &vaoID);
        Unbind();
        std::cout<<"Mesh: Deleted."<<std::endl;
    }
    onGPU=false;
}


template<class V, class E>
void Mesh<V,E>::Bind()
{
    glBindVertexArray(vaoID);
}


template<class V, class E>
void Mesh<V,E>::Unbind()
{
    glBindVertexArray(0);
}

template<class V, class E>
void Mesh<V,E>::RenderMesh()
{
    glDrawElements(GL_TRIANGLES, ebo.pBuffers->size(), E::DATA_TYPE, nullptr);
}


} // namespace pm
#endif // PM_MESH_H
