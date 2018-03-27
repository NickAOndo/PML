/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: GameWindow header.
*******************************************************************/

#ifndef PM_GAMEWINDOW_H
#define PM_GAMEWINDOW_H

#include <GL/glew.h> //BEFORE SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "PML/PhaseRelay.h"
namespace pm{

class GameWindow
{
    public:
        GameWindow();
        ~GameWindow();
        GameWindow(const GameWindow& other);

        void LoadWindow(  );
        void ClearWindow();
        void UpdateWindow( pm::PhaseRelay& p_relay );
        void LoadWindow( SDL_Window* pwin, SDL_GLContext context );

    protected:
    private:
        GameWindow& operator=(const GameWindow& other);

        SDL_Window* pWindow;
        SDL_GLContext glContext;
};


}
#endif // GAMEWINDOW_H
