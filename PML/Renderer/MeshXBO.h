/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Template class handles custom-data types.
        - Works with Mesh class to make buffer objects (VBO, EBO).
*******************************************************************/

#ifndef PM_MESHXBO_H
#define PM_MESHXBO_H

#include <string> // STL
#include <iostream>
#include <vector>
#include <memory>
 // Middleware
#include <GL/glew.h>
namespace pm {


template <class B>
class MeshXBO
{
public:
    MeshXBO(std::shared_ptr<std::vector<B>> pBuffers,
            const GLenum BUFFER_ARRAY_TYPE,
            const GLenum DRAW_TYPE);
    MeshXBO(const MeshXBO& other);
    ~MeshXBO();

    void GenerateBuffers();
    void UpdateBuffers();
    void Delete();

    std::shared_ptr<std::vector<B>> pBuffers;
    GLuint bufferID;
    const GLenum BUFFER_ARRAY_TYPE;
	const GLenum DRAW_TYPE;
    bool onGPU;


private:
    MeshXBO& operator=(const MeshXBO& other);
};

// IMPLEMENTATION OF TEMPLATE

template <class B>
MeshXBO<B>::MeshXBO( std::shared_ptr<std::vector<B>> pBuffers,
                     const GLenum BUFFER_ARRAY_TYPE,
                     const GLenum DRAW_TYPE)
:pBuffers(pBuffers),
bufferID(0),
BUFFER_ARRAY_TYPE(BUFFER_ARRAY_TYPE),
DRAW_TYPE(DRAW_TYPE),
onGPU(false)
{}


template<class B> // Copies only the smart pointer & type info
MeshXBO<B>::MeshXBO(const MeshXBO& other)
:pBuffers(other.pBuffers),
bufferID(0),
BUFFER_ARRAY_TYPE(other.BUFFER_ARRAY_TYPE),
DRAW_TYPE(other.DRAW_TYPE),
onGPU(false)
{}


template <class B>
MeshXBO<B>::~MeshXBO()
{
    Delete();
    bufferID=0;
}


template <class B>
void MeshXBO<B>::GenerateBuffers( )
{
	glGenBuffers(1, &bufferID);
	onGPU = true;
    UpdateBuffers();
}


template <class B>
void MeshXBO<B>::UpdateBuffers()
{
    glBindBuffer(BUFFER_ARRAY_TYPE, bufferID);
    glBufferData(BUFFER_ARRAY_TYPE, pBuffers->size()*sizeof(B), & (*pBuffers.get())[0], DRAW_TYPE );
}


template <class B>
void MeshXBO<B>::Delete()
{
	if(onGPU)
	{
		glDeleteBuffers(1,&bufferID);
	}
    onGPU=false;
}


} // namespace pm
#endif // PM_MESHXBO_H
