/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Utils for Texture class src.
        -- ConvertTextureRBGA, which turns all pixels of a key color
           into pure alpha pixels.
*******************************************************************/

#include "PML/Renderer/TextureUtil.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
namespace pm {

void ConvertTextureRGBA(SDL_Surface*& image)
{
    SDL_Surface* converter = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA8888, 0);
    SDL_FreeSurface(image);
    image = converter;
}


void ApplyColorKey(SDL_Surface* image, bool useColorKey, Uint8 r, Uint8 b, Uint8 g)
{
    Uint32* pixels = (Uint32*)image->pixels;
    Uint32 colorKey = SDL_MapRGBA(image->format, r, b, g, 0xFF);
    Uint32 transparency = SDL_MapRGBA( image->format, 0xFF, 0xFF, 0xFF, 0x00 );
    int numPixels = ( image->pitch / 4 ) * image->h;  // Divide by 4 b/c we're using 4-byte colors

    for( int i = 0; i < numPixels; ++i )
    {
        if( pixels[i] == colorKey )
            pixels[i] = transparency;
    }
}


} // namespace pm
