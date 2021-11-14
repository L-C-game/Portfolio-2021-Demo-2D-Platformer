/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

#include "GameObject.h"
#include "Ceiling.h"

Ceiling::Ceiling(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_CEILING);
	SetUpdateOrder(updateOrder::UPDATE_ORDER_CEILING);
	this->SetHalfSize({ (g_DISPLAY_WIDTH/2), (g_PIXELS_PER_UNIT) });
}

void Ceiling::Spawn(GameState& gameState)
{
	Point2f initialPos = { (g_DISPLAY_WIDTH / 2), -g_ZOOL_SIZE };
	GameObject* ceiling = new Ceiling(initialPos - gameState.camera.pos);
	ceiling->SetActive(true);
}

void Ceiling::Update(GameState& gameState)
{
	gameState;
}

void Ceiling::Draw(GameState& gameState) const
{
	gameState;
}