// Abstract base class for the PlayerState to inherit from
// This is the interface that will enforce the methods into the concrete states

#pragma once
#include "Player.h"
#include "Play.h"
#include "MainGame.h"

/* Forward declaration of the Player class to solve the circular dependency
 This alerts the compiler that there is a class called player,
 but doesn't tell the compiler about player's contents. */
class Player;

class PlayerState
{
public:
	// Pure virtual base methods to be overridden by the concrete states
	virtual void StateEnter(Player* player) = 0;
	virtual void HandleInput(Player* player) = 0;
	virtual void SetupBB(Player* player) = 0;
	virtual void DrawPlayer(const Player* player, GameState& state) const = 0;
	virtual void StateExit(Player* player) = 0;

	// public virtual destructor as this is a base class
	virtual ~PlayerState(){};
};