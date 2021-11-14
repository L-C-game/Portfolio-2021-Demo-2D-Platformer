/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

#include "GameObject.h"
#include "Pickup.h"

Pickup::Pickup(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_PICKUP);
	SetUpdateOrder(updateOrder::UPDATE_ORDER_PICKUP);
	SetDrawOrder(drawOrder::DRAW_ORDER_PICKUP);
	SetConstPos(pos);
	SetIsCollectable(true);
	SetSolid(false);
	SetHalfSize({g_HALF_SIZE_SMALL_OBJ, g_HALF_SIZE_SMALL_OBJ});
}

void Pickup::Spawn(PickUpData& pickupData)
{
	GameObject* pickupG = new Pickup(pickupData.pos);
	Pickup* pickup = static_cast<Pickup*>(pickupG);
	pickup->SetPointValue(pickupData.pointValue);
	pickup->SetPickUpID(pickupData.pickupSprite);
	pickup->SetActive(true);
}

void Pickup::Update(GameState& gameState)
{
	SetPosition(GetConstPos());
	gameState;
}

void Pickup::Draw(GameState& gameState) const
{
	Play::DrawSprite(GetPickUpID(), GetPosition() - gameState.camera.pos, static_cast<int>(g_SINGLE_FRAME_ANIM_SPEED * gameState.time));
}