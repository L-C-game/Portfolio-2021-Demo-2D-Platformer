/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

#include "GameObject.h"
#include "RightBarrier.h"

RBarrier::RBarrier(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_RBARRIER);
	SetUpdateOrder(updateOrder::UPDATE_ORDER_RBARRIER);
	SetStatic(true);
	SetHalfSize({ (ZOOL_SIZE), (LEVEL_HEIGHT / 2) });
}

void RBarrier::Spawn(GameState& gameState)
{
	// Right barrier constructor
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_RBARRIER) < 1)
	{
		Point2f initialPos = { (LEVEL_WIDTH + ZOOL_SIZE), (LEVEL_HEIGHT /2) };
		GameObject* rBarrier = new RBarrier(initialPos - gameState.camera.pos);
		rBarrier->SetActive(true);
	}
}

void RBarrier::Update(GameState& gameState) 
{

}

void RBarrier::Draw(GameState& gameState) const {}