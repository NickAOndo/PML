/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Texture class header.
        -- Uses SDL2 and SDL2_image to load and manage
        -- Loads, deletes, and binds textures on GPU.
*******************************************************************/


#ifndef PM_TEXTURE_H
#define PM_TEXTURE_H

#include <GL/glew.h> // Middleware
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
namespace pm{

class Texture
{
public:
    Texture();
    virtual ~Texture();
    Texture(const Texture& other);

    void LoadTexture(const char* fileName="assets/temp_image.png");
    void BindTexture();

protected:
private:
    Texture& operator=(const Texture& other);

    GLuint w;
    GLuint h;
    GLuint textureID;
    bool onGPU;
};

}
#endif // PM_TEXTURE_H
