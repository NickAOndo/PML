/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: ALPHA STAGE header.  Feature to be added.
        -- Manages Renderer objects, both memory and render-phase
           behavior.
*******************************************************************/

#ifndef PM_RENDERERMANAGER_H
#define PM_RENDERERMANAGER_H

#include <map> // STL
#include <memory>
#include "PML/Renderer/Mesh.h"
#include "PML/Renderer/ShaderProgram.h"
#include "PML/Renderer/Texture.h"
#include "PML/Renderer/Renderer.h"
namespace pm {

class RendererManager
{
public:
    RendererManager();
    ~RendererManager();
protected:
private:
    RendererManager(const RendererManager& other);
    RendererManager& operator=(const RendererManager& other);

    void GenerateRoutine( const char* fileName );
    void AddMesh();
    void AddTexture();
    void AddUniform();

    std::map<GLuint, std::shared_ptr<MeshAdapter>> meshes;
    std::map<GLuint, std::shared_ptr<ShaderProgramAdapter>> programs;
    std::map<GLuint, std::shared_ptr<Texture>> textures;
    std::map<GLuint, std::shared_ptr<UniformAdapter>> uniforms;

    std::map<GLuint, std::shared_ptr<Renderer>> routines;
};

} // namespace pm

#endif // PM_RENDERERMANAGER_H
