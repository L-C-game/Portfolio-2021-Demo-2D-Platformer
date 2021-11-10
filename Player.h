/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

#pragma once
#include "Play.h"
#include "GameObject.h"
#include "PlayerStateInterface.h"

class PlayerState;

class Player : public GameObject
{
public:
	Player(Point2f pos);

	~Player() 
	{
		SetActive(false);
	}

	// Spawning the player
	static void Spawn();

	// Getters and setters
	PlayerState* GetPlayerState() const { return m_pStateCurrent; }
	// Sets the Initial state of the player
	void SetInitialPlayerState();
	void SetPlayerState(PlayerState& pStateNew);

	void SetIsLeftFacing(bool isLeftFacing) { m_isLeftFacing = isLeftFacing; }
	bool GetIsLeftFacing() const { return m_isLeftFacing; }

	void SetIsGrounded(bool isGrounded) { m_isGrounded = isGrounded; }
	bool GetIsGrounded() const { return m_isGrounded; }

	void SetHealth(int health) { m_health = health; }
	int GetHealth() const { return m_health; }

	void SetScore(int score) { m_score = score; }
	int GetScore() const { return m_score; }

	void SetPlayerID(int playerID) { m_playerID = playerID; }
	int GetPlayerID() const { return m_playerID; }

	void SetAnimSpeed(int animSpeed) { m_animSpeed = animSpeed; }
	int GetAnimSpeed() const { return m_animSpeed; }

	void SetJumpTimer(int jumpTimer) { m_jumpTimer = jumpTimer; }
	int GetJumpTimer() const { return m_jumpTimer; }

	void SetIsHurt(bool isHurt) { m_isHurt = isHurt; }
	bool GetIsHurt() const { return m_isHurt; }

	void SetiFramesTimer(int iFramesTimer) { m_iFramesTimer = iFramesTimer; }
	int GetiFramesTimer() const { return m_iFramesTimer; }

	void SetIsBlinking(bool isBlinking) { m_isBlinking = isBlinking; }
	bool GetIsBlinking() const { return m_isBlinking; }

	void SetBlinkTimer(int blinkTimer) { m_blinkTimer = blinkTimer; }
	int GetBlinkTimer() const { return m_blinkTimer; }

	void SetHasUltimate(bool hasUltimate) { m_hasUltimate = hasUltimate; }
	bool GetHasUltimate() const { return m_hasUltimate; }

	// Resets the player to the start of the map with full health and 0 points
	void ResetPlayer();

	// Handles the specific behaviour when the player collides with particular objects
	void CollisionSystem(GameState& gameState);

	void CentreCameraOnPlayer(GameState& gameState);

	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;

private:
	
	PlayerState* m_pStateCurrent{nullptr};
	bool m_isLeftFacing{ false };
	bool m_isGrounded{ true };
	int m_health{ MAX_HEALTH_PLAYER };
	bool m_isHurt{ false };
	int m_playerID{ zoolIdleRpng };
	int m_animSpeed{ SINGLE_FRAME_ANIM_SPEED };
	int m_score{ 0 };

	// time elasped since entering jump state in frames
	int m_jumpTimer{ 0 };
	// invincibility frames timer
	int m_iFramesTimer{ 0 };

	// Variables to blink the sprite
	int m_isBlinking{ false };
	int m_blinkTimer{ 0 };

	// Boolean for ultimate pickup
	bool m_hasUltimate{ false };
};
