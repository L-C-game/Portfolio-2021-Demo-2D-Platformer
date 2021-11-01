#include "GameObject.h"
#include "Block.h"

Block::Block(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_BLOCK);
	SetUpdateOrder(7);
	SetDrawOrder(7);
	SetStatic(true);
	SetConstPos(pos);
	blocks.push_back(this);
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
	}
}

void Block::BreakBlock()
{
	this->SetBlockState(BlockState::BREAK_STATE);
}

void Block::RemoveBlock()
{
	this->SetTimer(this->GetTimer() + 1);

	if (this->GetTimer() >= BLOCK_BREAK_ANIM_SPEED)
	{
		this->SetActive(false);
	}
}

void Block::Update(GameState& gameState)
{
	this->SetPosition(this->GetConstPos());

	switch (GetBlockState())
	{
	case BlockState::STABLE_STATE:
		break;
	case BlockState::BREAK_STATE:
		this->UpdateBreak();
		break;
	}
}

void Block::UpdateStable() {};

void Block::UpdateBreak()
{
	this->SetBlockID(spriteIdInts::blockbreakpng);
	this->SetAnimSpeed(BLOCK_BREAK_ANIM_SPEED);
	this->RemoveBlock();
}

void Block::Draw(GameState& gameState) const
{
	Play::DrawSprite(GetBlockID(), GetPosition() - gameState.camera.pos, static_cast<int>((GetAnimSpeed() * gameState.time)));
}
