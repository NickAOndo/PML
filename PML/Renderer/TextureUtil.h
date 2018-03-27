/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Utils for Texture class header.
        -- ConvertTextureRBGA, which turns all pixels of a key color
           into pure alpha pixels.
*******************************************************************/

#ifndef PM_CONVERTTEXTUREFORMAT_H
#define PM_CONVERTTEXTUREFORMAT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace pm {

void ConvertTextureRGBA( SDL_Surface*& image);
void ApplyColorKey(SDL_Surface* image, bool useColorKey=false, Uint8 r=0, Uint8 b=0, Uint8 g=0);

} // namespace pm
#endif // PM_CONVERTTEXTUREFORMAT_H
