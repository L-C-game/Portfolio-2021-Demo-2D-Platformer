#pragma once
#include "PlayerStateInterface.h"
#include "Player.h"

class IdleState : public PlayerState
{
public:
	void StateEnter(Player* player) {}
	void HandleInput(Player* player); // Implemented in cpp
	void DrawPlayer(const Player* player, GameState& state) const;
	void StateExit(Player* player) {}

	// Controls access to the singleton instance, 
	static PlayerState& getInstance();

private:
	IdleState() {}
	// Prevents the singleton from being cloned
	IdleState(const IdleState& other) = delete;
	// Prevents the singleton from being assigned
	void operator=(const IdleState&) = delete;
};

class WalkState : public PlayerState
{
public:
	void StateEnter(Player* player) {}
	void HandleInput(Player* player); // Implemented in cpp
	void DrawPlayer(const Player* player, GameState& state) const;
	void StateExit(Player* player) {}

	// Controls access to the singleton instance, 
	static PlayerState& getInstance();
private:
	WalkState() {}
	// Prevents the singleton from being cloned
	WalkState(const WalkState& other) = delete;
	// Prevents the singleton from being assigned
	void operator=(const WalkState&) = delete;
};
