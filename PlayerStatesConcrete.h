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

class CrouchState : public PlayerState
{
public:
	void StateEnter(Player* player) {}
	void HandleInput(Player* player); // Implemented in cpp
	void DrawPlayer(const Player* player, GameState& state) const;
	void StateExit(Player* player) {}

	// Controls access to the singleton instance, 
	static PlayerState& getInstance();
private:
	CrouchState() {}
	// Prevents the singleton from being cloned
	CrouchState(const CrouchState& other) = delete;
	// Prevents the singleton from being assigned
	void operator=(const CrouchState&) = delete;
};

class JumpState : public PlayerState
{
public:
	void StateEnter(Player* player) {}
	void HandleInput(Player* player); // Implemented in cpp
	void DrawPlayer(const Player* player, GameState& state) const;
	void StateExit(Player* player) {}

	// Controls access to the singleton instance, 
	static PlayerState& getInstance();
private:
	JumpState() {}
	// Prevents the singleton from being cloned
	JumpState(const JumpState& other) = delete;
	// Prevents the singleton from being assigned
	void operator=(const JumpState&) = delete;
};

class FallState : public PlayerState
{
public:
	void StateEnter(Player* player) {}
	void HandleInput(Player* player); // Implemented in cpp
	void DrawPlayer(const Player* player, GameState& state) const;
	void StateExit(Player* player) {}

	// Controls access to the singleton instance, 
	static PlayerState& getInstance();
private:
	FallState() {}
	// Prevents the singleton from being cloned
	FallState(const FallState& other) = delete;
	// Prevents the singleton from being assigned
	void operator=(const FallState&) = delete;
};
