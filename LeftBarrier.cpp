/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

#include "GameObject.h"
#include "LeftBarrier.h"

LBarrier::LBarrier(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_LBARRIER);
	SetUpdateOrder(updateOrder::UPDATE_ORDER_LBARRIER);
	SetStatic(true);
	SetHalfSize({(ZOOL_SIZE), (LEVEL_HEIGHT/2)});
}

void LBarrier::Spawn(GameState& gameState)
{
	// Left barrier constructor
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_LBARRIER) < 1)
	{
		Point2f initialPos = { -(ZOOL_SIZE), (LEVEL_HEIGHT/2) };
		GameObject* lBarrier = new LBarrier(initialPos - gameState.camera.pos);
		lBarrier->SetActive(true);
	}
}

void LBarrier::Update(GameState& gameState) {}

void LBarrier::Draw(GameState& gameState) const {}