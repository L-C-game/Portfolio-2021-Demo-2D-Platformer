#pragma once
#include "Play.h"
#include "GameObject.h"
#include "PlayerStateInterface.h"

class PlayerState;

class Player : public GameObject
{
public:

	//const int spriteID = Play::GetSpriteId("player_idle");
	//float spriteWidth = Play::GetSpriteWidth(spriteID);
	//float halfSpriteWidth = spriteWidth / 2;

	Player(Point2f pos);

	~Player() {}

	// Spawning the player
	static void Spawn(GameState& state);

	// Getters and setters
	PlayerState* GetPlayerState() const { return m_pStateCurrent; }
	void SetPlayerState(PlayerState& pStateNew);

	void SetIsLeftFacing(bool isLeftFacing) { m_isLeftFacing = isLeftFacing; }
	bool GetIsLeftFacing() const { return m_isLeftFacing; }

	// Game Object overrides
	void Update(GameState& state) override;
	void Draw(GameState& state) const override;

	//// Specific Update functions
	//void IdleUpdate(GameState& state);
	//void WalkUpdate(GameState& state);

	//// Specific draw functions
	//void IdleDraw(GameState& state) const;
	//void WalkDraw(GameState& state) const;

private:
	PlayerState* m_pStateCurrent;
	bool m_isLeftFacing{ false };
};