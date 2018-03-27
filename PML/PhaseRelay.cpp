/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: PhaseRelay object file.
     (for storing game states between draw and update phases.)
*******************************************************************/

#include "PhaseRelay.h"
namespace pm{

PhaseRelay::PhaseRelay()
:gameStatus(false)
,frames(0)
{
	gameStatus = true;
}

PhaseRelay::~PhaseRelay()
{}

PhaseRelay::PhaseRelay(const PhaseRelay& other)
{}

PhaseRelay& PhaseRelay::operator=(const PhaseRelay& rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

} //end namespace
