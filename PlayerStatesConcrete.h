/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game

	Finite state machine built using the state design pattern and Meyer's Singleton for thread safety.
	The following references were used to help me understand and implement the pattern in my own game
	References:
	Meyer's Singleton:
	http://laristra.github.io/flecsi/src/developer-guide/patterns/meyers_singleton.html
	State Pattern:
	https://gameprogrammingpatterns.com/state.html
	Additional resources for understanding implementation:
	https://www.aleksandrhovhannisyan.com/blog/finite-state-machine-fsm-tutorial-implementing-an-fsm-in-c/

	Each of the states is represented as it's own class with method's that override the pure virtual base methods of the interface. 
	The states have been implemented as singleton's so there is only a single instance of each in memory.
	While this works well with the current game design as there is only a single player it would not work if there were 2 instances of the player.

	By using the State design pattern, each of the states are more self contained but also share methods that are relevant to all of them,
	this helps avoid repeating code.

	Each of the states have entry and exit methods which allow for sounds to be played and flags and other variables to be reset.


*/

#pragma once
#include "PlayerStateInterface.h"
#include "Player.h"

class IdleState : public PlayerState
{
public:
	void StateEnter(Player& player) override;
	void HandleInput(Player& player) override;

	void DrawPlayer(const Player& player, GameState& gameState) const override;
	void StateExit(Player& player) override;
	void SetupAnim(Player& player) override;
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
	void StateEnter(Player& player) override;
	void HandleInput(Player& player) override;
	void DrawPlayer(const Player& player, GameState& gameState) const override;
	void StateExit(Player& player) override;
	void SetupAnim(Player& player) override;
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
	void StateEnter(Player& player) override;
	void HandleInput(Player& player) override;
	void DrawPlayer(const Player& player, GameState& gameState) const override;
	void StateExit(Player& player) override;
	void SetupAnim(Player& player) override;
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
	void StateEnter(Player& player) override;
	void HandleInput(Player& player) override;
	void DrawPlayer(const Player& player, GameState& gameState) const override;
	void StateExit(Player& player) override;
	void SetupAnim(Player& player) override;
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
	void StateEnter(Player& player) override;
	void HandleInput(Player& player) override;
	void DrawPlayer(const Player& player, GameState& gameState) const override;
	void StateExit(Player& player) override;
	void SetupAnim(Player& player) override;
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
	void StateEnter(Player& player) override;
	void HandleInput(Player& player) override;
	void DrawPlayer(const Player& player, GameState& gameState) const override;
	void StateExit(Player& player) override;
	void SetupAnim(Player& player) override;
	// Controls access to the singleton instance, 
	static PlayerState& getInstance();
private:
	FallState() {}
	// Prevents the singleton from being cloned
	FallState(const FallState& other) = delete;
	// Prevents the singleton from being assigned
	void operator=(const FallState&) = delete;
};

class HurtState : public PlayerState
{
public:
	void StateEnter(Player& player) override;
	void HandleInput(Player& player) override;
	void DrawPlayer(const Player& player, GameState& gameState) const override;
	void StateExit(Player& player) override;
	void SetupAnim(Player& player) override;
	// Controls access to the singleton instance, 
	static PlayerState& getInstance();
private:
	HurtState() {}
	// Prevents the singleton from being cloned
	HurtState(const HurtState& other) = delete;
	// Prevents the singleton from being assigned
	void operator=(const HurtState&) = delete;
};