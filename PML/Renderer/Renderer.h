/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: ALPHA STAGE header.  Feature marked to be added.
        -- Handles Mesh, ShaderProgram, and Texture for renderering.
*******************************************************************/

#ifndef PM_RENDERER_H
#define PM_RENDERER_H

#include <map> // STL
#include <vector>
#include <memory>
#include "PML/Renderer/Mesh.h"
#include "PML/Renderer/Uniform.h"
#include "PML/Renderer/ShaderProgram.h"
#include "PML/Renderer/Texture.h"
#include "PML/Renderer/Renderer.h"

namespace pm {

template <class B>
using pArray = std::vector<std::vector<std::shared_ptr<B>>>;

class Renderer
{
public:
    Renderer();
    ~Renderer();
    Renderer(const Renderer& other);

protected:
private:
    Renderer& operator=(const Renderer& other);

    pArray<MeshAdapter> meshes;
    pArray<ShaderProgramAdapter> programs;
    pArray<Texture> textures;
    pArray<UniformAdapter> uniforms;
};

} // namespace pm

#endif // PM_RENDERER_H
