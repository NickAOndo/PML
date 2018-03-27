/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Texture class src.
        -- Uses SDL2 and SDL2_image to load and manage
        -- Loads, deletes, and binds textures on GPU.
*******************************************************************/

#include "Texture.h"

#include <iostream> //STL
#include <GL/glew.h> // Middleware
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include "PML/Renderer/TextureUtil.h" // PML
namespace pm{

Texture::Texture()
:w(0),
h(0),
textureID(0),
onGPU(false)
{}

Texture::~Texture()
{
    //dtor
    if( onGPU )
    {
        glDeleteTextures(1,&textureID);
        std::cout<<"Texture: Deleted."<<std::endl;
    }
}

Texture::Texture(const Texture& other)  // Blank-copying
:w(0),
h(0),
textureID(0),
onGPU(false)
{}


void Texture::LoadTexture(const char* fileName)
{
    std::string imageFile = "assets/"+std::string(fileName)+".png";
	SDL_Surface* image = IMG_Load( imageFile.c_str() ); // Get temporary image

	// Check if image loaded, make sure pointer is valid
    if ( !image )
    {
        std::cout<<"Error Texture: IMG: "<<IMG_GetError()<<std::endl;
    }
    else
    {
        std::cout<<"Texture: Loaded image into RAM."<<std::endl;
        w = image->w;
        h = image->h;

        if( image->format->BytesPerPixel == 3 )
        {
            // USE COLORKEY: R=0 (0), G=148 (0x94), B=255 (0xff)
            ConvertTextureRGBA(image);
        }
        else if ( image->format->BytesPerPixel != 4 )
        {
            std::cout<<"Texture Error: Cannot load non 24-bit/32-bit image formats!"<<std::endl;
        }

        ApplyColorKey(image, true, 0, 148, 255);

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
        onGPU = true;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        std::cout<<"Texture: Loaded to VRAM."<<std::endl;
    }
    SDL_FreeSurface( image );
}

void Texture::BindTexture()
{
    if( onGPU )
        glBindTexture(GL_TEXTURE_2D, textureID);
    else
        std::cout<<"Texture Error: Cannot bind empty texture!"<<std::endl;
}


} // end namespace
