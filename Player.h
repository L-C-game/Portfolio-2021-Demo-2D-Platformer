#pragma once
#include "Play.h"
#include "GameObject.h"

class Player : public GameObject
{
public:

	//const int spriteID = Play::GetSpriteId("player_idle");
	//float spriteWidth = Play::GetSpriteWidth(spriteID);
	//float halfSpriteWidth = spriteWidth / 2;

	Player(Point2f pos) : GameObject(pos)
	{
		SetType(Type::OBJ_PLAYER);
		SetUpdateOrder(0);
		SetDrawOrder(0);
		
	}

	~Player() {}

	enum class PlayerState
	{
		STATE_NULL = -1,
		STATE_IDLE = 0,
		STATE_WALK,
		STATE_JUMP,
		STATE_CROUCH
		// May add states for taking damage and dodging
	};

	// Spawning the player
	static void Spawn(GameState& state);

	// Getters and setters
	void SetPlayerState(int pState) { m_playerState = pState; }
	int GetPlayerState() const { return m_playerState; }
	void SetIsLeftFacing(bool isLeftFacing) { m_isLeftFacing = isLeftFacing; }
	bool GetIsLeftFacing() const { return m_isLeftFacing; }

	// Game Object overrides
	void Update(GameState& state) override;
	void Draw(GameState& state) const override;

	// Specific Update functions
	void IdleUpdate(GameState& state);
	void WalkUpdate(GameState& state);

	// Specific draw functions
	void IdleDraw(GameState& state) const;
	void WalkDraw(GameState& state) const;

private:
	int m_playerState{ 0 };
	bool m_isLeftFacing{ false };
};