/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Game class object file.
*******************************************************************/

#include "Game.h"

#include <math.h>
#include <vector> // STL
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <GL/glew.h> //Middleware
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "PML/PhaseRelay.h"
#include "PML/GameWindow.h" // PML
#include "PML/Stage/Stage.h"
#include "PML/Renderer/Texture.h"
#include "PML/Renderer/ShaderProgram.h"
#include "PML/Renderer/Mesh.h"
namespace pm{

Game::Game(const char* gameName)
:pGameWindow( std::make_unique<GameWindow>() )
,stageList()
,phRelay()
{
    std::cout<<"Game started."<<std::endl;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout<<"Game: SDL init error! SDL2 Error: "<<SDL_GetError()<<std::endl;
    }
    else
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 5);
        SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 5 );
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    }

    pGameWindow->LoadWindow();
	stageList.push_back(std::make_shared<pm::Stage>());
	//stageList[0]->LoadStage(PM_STAGE_MENU, phRelay);
}

Game::~Game()
{
    stageList[0].reset();
    pGameWindow.reset(); // Release and delete the Window before exiting SDL!
    SDL_Quit();
    std::cout<<"Game: SDL2 quit."<<std::endl;
    std::cout<<"Game finished."<<std::endl;
}

Game::Game(const Game& other)
{
    //copy ctor
}

Game& Game::operator=(const Game& rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

void Game::MainLoop()
{
    vec3 nPos = vec3(-0.5f,+0.5f,+0.0f);
    GLfloat w = 1.0f;
    GLfloat h = 1.0f;
    stageList[0]->AddStageActor( nPos, w, h );

    auto pTransform = std::make_shared<std::vector<Transform>>();
    ShaderProgram<Vertex> program;
    program.LoadProgram("temp");

    Texture image;
    image.LoadTexture("temp");

    vec3 position(0.0f, 0.0f, -2.6f);
    Transform uniform(position, 57.0f, 1360.0f/768.0f, 0.01f, 1000.0f );

    SDL_Event event;

    // Main Loop
    while( IsRunning() )
    {
        phRelay.frames +=1;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
			{
				phRelay.gameStatus = false;
            }
        }
        pGameWindow->ClearWindow();
        program.UseProgram();
        uniform.UpdateUniform(program.programID, phRelay);
        image.BindTexture();
        stageList[0]->UpdateStage(phRelay);
        stageList[0]->DrawActors();
        pGameWindow->UpdateWindow(phRelay);
    }
    std::cout<<"Game: Updates completed: "<<phRelay.frames<<std::endl;
}

}
