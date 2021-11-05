#include "GameObject.h"
#include "Block.h"

Block::Block(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_BLOCK);
	SetUpdateOrder(7);
	SetDrawOrder(7);
	SetStatic(true);
	SetSolid(true);
	SetConstPos(pos);
	blocks.push_back(this);
	SetBlockState(BlockState::STABLE_STATE);
}

void Block::Spawn(BlockData& blockData)
{
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_BLOCK) < (BLOCK_AMOUNT + 1))
	{
		GameObject* blockG = new Block(blockData.pos);
		blockG->SetHalfSize(blockData.HalfSizeBlock);
		Block* block = static_cast<Block*>(blockG);
		block->SetBlockID(blockData.blockSprite);
		block->SetTimer(0);
		block->SetActive(true);
	}
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
}

void Block::UpdateStable() 
{
	SetTimer(0);
	SetSolid(true);
	SetHalfSize({ HALF_SIZE_SMALL_OBJ, HALF_SIZE_SMALL_OBJ });
	SetAnimSpeed(0);
}

void Block::UpdateBreak()
{
	SetBlockID(spriteIdInts::blockbreakpng);
	SetAnimSpeed(BLOCK_BREAK_ANIM_SPEED);
	SetTimer(GetTimer() + 1);

	if (GetTimer() >= 2 * BLOCK_BREAK_ANIM_SPEED)
	{
		SetBlockState(BlockState::BROKEN_STATE);
		SetSolid(false);
	}
}

void Block::UpdateBroken()
{
	SetTimer(GetTimer() + 1);

	if (GetTimer() >= BLOCK_REAPPEAR)
	{
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

