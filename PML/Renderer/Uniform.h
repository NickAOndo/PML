/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: ALPHA STAGE.  Uniform class header.
        -- Part of the UBO (Uniform Buffer Object) feature.
        -- Will be added in future commit.
*******************************************************************/

#ifndef PM_UNIFORM_H
#define PM_UNIFORM_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "PML/Renderer/XBObuffer.h"

namespace pm {

class UniformAdapter
{
public:
    UniformAdapter();
    virtual ~UniformAdapter();
    UniformAdapter(const UniformAdapter& other);

protected:
private:
    UniformAdapter& operator=(const UniformAdapter& other);
};

template<class T>
class Uniform : public UniformAdapter
{
public:
    Uniform(T& type);
    virtual ~Uniform();
    Uniform(const Uniform& other);

protected:
private:
    UniformAdapter& operator=(const UniformAdapter& other);
};


template<class T>
Uniform<T>::Uniform(T& type)
{
    //ctor
}


template<class T>
Uniform<T>::~Uniform()
{
    //dtor
}


template<class T>
Uniform<T>::Uniform(const Uniform& other)
{
    //copy ctor
}


} // namespace pm
#endif // PM_UNIFORM_H
