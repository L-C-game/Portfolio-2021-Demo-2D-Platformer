/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

#pragma once
#include "GameObject.h"
class Block :public GameObject
{
public:
	enum class BlockState
	{
		NULL_STATE =-1,
		STABLE_STATE,
		BREAK_STATE,
		BROKEN_STATE
	};

	Block(Point2f pos);

	~Block() 
	{
		SetActive(false);
	};
	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;

	static void Spawn(BlockData& blockData);

	void SetConstPos(Point2f constPos) { m_constPos = constPos; }
	Point2f GetConstPos() const { return m_constPos; }

	void SetTimer(int timer) { m_timer = timer; }
	int GetTimer() const { return m_timer; }

	void SetBlockID(int blockID) { m_blockID = blockID; }
	int GetBlockID() const { return m_blockID; }

	void SetAnimSpeed(int animSpeed) { m_animSpeed = animSpeed; }
	int GetAnimSpeed() const { return m_animSpeed; }

	void SetBlockState(BlockState blockState) { m_state = blockState; }
	BlockState GetBlockState() const { return m_state; }

	void StableDraw(GameState& gameState) const;
	void BreakDraw(GameState& gameState) const;
	void BrokenDraw(GameState& gameState) const;

	void UpdateStable();
	void UpdateBreak();
	void UpdateBroken();

private:
	Point2f m_constPos{ 0.0f, 0.0f };
	int m_timer{ 0 };
	int m_blockID{ blockpng };
	int m_animSpeed{ g_SINGLE_FRAME_ANIM_SPEED };
	BlockState m_state{BlockState::STABLE_STATE};
};

