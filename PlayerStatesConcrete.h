#pragma once
#include "PlayerStateInterface.h"
#include "Player.h"

class IdleState : public PlayerState
{
public:
	void StateEnter(Player& player);
	void HandleInput(Player& player);

	// Might have to edit this as we don't want the collision to be pixel perfect as it makes gameplay awkward
	//void SetupBB(Player& player);
	void DrawPlayer(const Player& player, GameState& gameState) const;
	void StateExit(Player& player);

	// Controls access to the singleton instance, 
	static PlayerState& getInstance();
	//std::string GetName() const { return m_name; };

private:
	IdleState() {}
	// Prevents the singleton from being cloned
	IdleState(const IdleState& other) = delete;
	// Prevents the singleton from being assigned
	void operator=(const IdleState&) = delete;
	// a string which hold the name of the state
	//std::string m_name{ "Idle" };
};

class WalkState : public PlayerState
{
public:
	void StateEnter(Player& player);
	void HandleInput(Player& player);
	void DrawPlayer(const Player& player, GameState& gameState) const;
	void StateExit(Player& player);

	// Controls access to the singleton instance, 
	static PlayerState& getInstance();
private:
	WalkState() {}
	// Prevents the singleton from being cloned
	WalkState(const WalkState& other) = delete;
	// Prevents the singleton from being assigned
	void operator=(const WalkState&) = delete;
};

class SkidState : public PlayerState
{
public:
	void StateEnter(Player& player);
	void HandleInput(Player& player);
	void DrawPlayer(const Player& player, GameState& gameState) const;
	void StateExit(Player& player);

	// Controls access to the singleton instance, 
	static PlayerState& getInstance();
private:
	SkidState() {}
	// Prevents the singleton from being cloned
	SkidState(const SkidState& other) = delete;
	// Prevents the singleton from being assigned
	void operator=(const SkidState&) = delete;
};

class CrouchState : public PlayerState
{
public:
	void StateEnter(Player& player);
	void HandleInput(Player& player);
	void DrawPlayer(const Player& player, GameState& gameState) const;
	void StateExit(Player& player);

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
	void StateEnter(Player& player);
	void HandleInput(Player& player);
	void DrawPlayer(const Player& player, GameState& gameState) const;
	void StateExit(Player& player);

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
	void StateEnter(Player& player);
	void HandleInput(Player& player);
	void DrawPlayer(const Player& player, GameState& gameState) const;
	void StateExit(Player& player);

	// Controls access to the singleton instance, 
	static PlayerState& getInstance();
private:
	FallState() {}
	// Prevents the singleton from being cloned
	FallState(const FallState& other) = delete;
	// Prevents the singleton from being assigned
	void operator=(const FallState&) = delete;
};
