/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game

	The block has 3 states:
	Stable - The initial state before the player collides with the block, animation speed is 0
	Breaking - Transition to this state is triggered by the collision between the player and the block.
	The breaking animation
	broken
*/

#include "GameObject.h"
#include "Block.h"

Block::Block(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_BLOCK);
	SetUpdateOrder(updateOrder::UPDATE_ORDER_BLOCK);
	SetDrawOrder(drawOrder::DRAW_ORDER_BLOCK);
	SetSolid(true);
	SetConstPos(pos);
	SetBlockState(BlockState::STABLE_STATE);
}

void Block::Spawn(BlockData& blockData)
{
	GameObject* blockG = new Block(blockData.pos);
	blockG->SetHalfSize(blockData.HalfSizeBlock);
	Block* block = static_cast<Block*>(blockG);
	block->SetBlockID(blockData.blockSprite);
	block->SetTimer(0);
	block->SetActive(true);
}

void Block::Update(GameState& gameState)
{
	SetPosition(GetConstPos());

	switch (GetBlockState())
	{
	case BlockState::STABLE_STATE:
		UpdateStable();
		break;
	case BlockState::BREAK_STATE:
		UpdateBreak();
		break;
	case BlockState::BROKEN_STATE:
		UpdateBroken();
		break;
	}

	gameState;
}

void Block::UpdateStable() 
{
	SetHalfSize({ g_HALF_SIZE_SMALL_OBJ, g_HALF_SIZE_SMALL_OBJ });
	SetAnimSpeed(0);
}

void Block::UpdateBreak()
{
	SetBlockID(spriteIdInts::blockbreakpng);
	SetAnimSpeed(g_BLOCK_BREAK_ANIM_SPEED);
	SetTimer(GetTimer() + 1);

	if (GetTimer() >= 2 * g_BLOCK_BREAK_ANIM_SPEED)
	{
		SetTimer(0);
		SetSolid(false);
		SetBlockState(BlockState::BROKEN_STATE);
	}
}

void Block::UpdateBroken()
{
	SetTimer(GetTimer() + 1);

	if (GetTimer() >= 2 * g_BLOCK_REAPPEAR)
	{
		SetSolid(true);
		SetTimer(0);
		SetBlockState(BlockState::STABLE_STATE);
	}
}

void Block::Draw(GameState& gameState) const
{
	switch (GetBlockState())
	{
	case BlockState::STABLE_STATE:
		StableDraw(gameState);
		break;
	case BlockState::BREAK_STATE:
		BreakDraw(gameState);
		break;
	case BlockState::BROKEN_STATE:
		BrokenDraw(gameState);
		break;
	}
}

void Block::StableDraw(GameState& gameState) const
{
	Play::DrawSprite(GetBlockID(), GetPosition() - gameState.camera.pos, static_cast<int>((GetAnimSpeed() * gameState.time)));
}

void Block::BreakDraw(GameState& gameState) const
{
	Play::DrawSprite(GetBlockID(), GetPosition() - gameState.camera.pos, static_cast<int>((GetAnimSpeed() * gameState.time / 2)));
}

void Block::BrokenDraw(GameState& gameState) const
{
	Play::DrawSpriteTransparent(GetBlockID(), GetPosition() - gameState.camera.pos, static_cast<int>((GetAnimSpeed() * gameState.time)), 0.0f);
}

