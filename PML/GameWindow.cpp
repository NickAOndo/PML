/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: GameWindow object file.
*******************************************************************/

#include "GameWindow.h"
#include <GL/glew.h> //BEFORE SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <string>
#include <sstream>

namespace pm{

GameWindow::GameWindow()
:pWindow(nullptr),
glContext(nullptr)
{
    //ctor
    std::cout<<"Empty GameWindow created!"<<std::endl;
}

GameWindow::~GameWindow()
{
    //dtor
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(pWindow);
    pWindow = nullptr;
    std::cout<<"GameWindow deleted!"<<std::endl;
}

GameWindow::GameWindow(const GameWindow& other)
:pWindow(nullptr),
glContext()
{
    //copy ctor
    std::cout<<"GameWindow null-copied!"<<std::endl;
}

GameWindow& GameWindow::operator=(const GameWindow& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void GameWindow::LoadWindow( )
{
    // Create Window + GLContext
	std::cout<<"GameWindow: Creating SDL2 Window."<<std::endl;
	pWindow = SDL_CreateWindow( "SDL2 GameWindow with OpenGL 3.2", 0, 0, 1360, 768, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL );
    std::cout<<"GameWindow: SDL_Window* = "<<pWindow<<std::endl;

	if(pWindow != nullptr)
	{
		glContext = SDL_GL_CreateContext( pWindow );
		glewExperimental = GL_TRUE;
		GLenum glewState = glewInit();

		if( glewState != GLEW_OK )
		{
			std::stringstream error;
			error<<glewGetErrorString(glewState);
			std::cout<<"GameWindow: Context: GLEW error: "<<error.str()<<std::endl;
		}
		else
		{
			std::cout<<"GameWindow: Created SDL2 Window with OpenGL Context!"<<std::endl;
		}
	}
	else
	{
        std::cout<<"GameWindow: SDL_Window* is a nullptr!"<<std::endl;
		std::cout<<"GameWindow: SDL2 Error: "<<SDL_GetError()<<std::endl;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GameWindow::ClearWindow()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameWindow::UpdateWindow( pm::PhaseRelay& phRelay )
{
    SDL_GL_SwapWindow(pWindow);
}

} //end namespace
