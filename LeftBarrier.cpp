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
	SetHalfSize({(g_ZOOL_SIZE), (g_LEVEL_HEIGHT/2)});
}

void LBarrier::Spawn(GameState& gameState)
{
	Point2f initialPos = { -(g_ZOOL_SIZE), (g_LEVEL_HEIGHT/2) };
	GameObject* lBarrier = new LBarrier(initialPos - gameState.camera.pos);
	lBarrier->SetActive(true);
}

void LBarrier::Update(GameState& gameState) 
{
	gameState;
}

void LBarrier::Draw(GameState& gameState) const 
{
	gameState;
}