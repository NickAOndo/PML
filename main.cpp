/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: Example Sandbox code for a main.
        -- Demonstrates basic access.
*******************************************************************/


#include "PML/PML.h"

int main(int argc, char *argv[])
{
    pm::Game myGame("My Game!");
    myGame.MainLoop();

    return 0;
}
