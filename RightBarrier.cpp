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
	SetHalfSize({ (g_ZOOL_SIZE), (g_LEVEL_HEIGHT / 2) });
}

void RBarrier::Spawn(GameState& gameState)
{
	Point2f initialPos = { (g_LEVEL_WIDTH + g_ZOOL_SIZE), (g_LEVEL_HEIGHT /2) };
	GameObject* rBarrier = new RBarrier(initialPos - gameState.camera.pos);
	rBarrier->SetActive(true);
}

void RBarrier::Update(GameState& gameState) 
{
	gameState;
}

void RBarrier::Draw(GameState& gameState) const 
{
	gameState;
}