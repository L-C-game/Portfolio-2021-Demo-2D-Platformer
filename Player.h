#pragma once
#include "Play.h"
#include "GameObject.h"
#include "PlayerStateInterface.h"

class PlayerState;

class Player : public GameObject
{
public:
	Player(Point2f pos);

	~Player() {}

	// Spawning the player
	static void Spawn();

	// Getters and setters
	PlayerState* GetPlayerState() const { return m_pStateCurrent; }
	void SetPlayerState(PlayerState& pStateNew);

	void SetIsLeftFacing(bool isLeftFacing) { m_isLeftFacing = isLeftFacing; }
	bool GetIsLeftFacing() const { return m_isLeftFacing; }

	void SetIsGrounded(bool isGrounded) { m_isGrounded = isGrounded; }
	bool GetIsGrounded() const { return m_isGrounded; }

	void CollisionSystem();

	// Game Object overrides
	void Update(GameState& state) override;
	void Draw(GameState& state) const override;

private:
	
	PlayerState* m_pStateCurrent;
	bool m_isLeftFacing{ false };
	bool m_isGrounded{ true };
};