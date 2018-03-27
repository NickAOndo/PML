/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Game class header.
*******************************************************************/

#ifndef PM_GAME_H
#define PM_GAME_H

#include <vector>
#include <memory>
#include "PML/GameWindow.h"
#include "PML/Stage/Stage.h"
#include "PML/PhaseRelay.h"
namespace pm{

class Game
{
public:
    Game(const char* gameName);
    ~Game();
    Game(const Game& other);
    Game& operator=(const Game& other);

    std::unique_ptr<pm::GameWindow> pGameWindow;
    std::vector<std::shared_ptr<pm::Stage>> stageList;
    pm::PhaseRelay phRelay;

    void MainLoop();
protected:
private:
    bool IsRunning() { return phRelay.gameStatus; }
};

}
#endif // GAME_H
