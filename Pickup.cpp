#include "GameObject.h"
#include "Pickup.h"

Pickup::Pickup(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_PICKUP);
	SetUpdateOrder(6);
	SetDrawOrder(6);
	SetStatic(true);
	SetConstPos(pos);
	SetIsCollectable(true);
	pickUps.push_back(this);
}

void Pickup::Spawn(PickUpData& pickupData)
{
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_PICKUP) < (PICKUP_AMOUNT + 1))
	{
		GameObject* pickupG = new Pickup(pickupData.pos);
		pickupG->SetHalfSize(pickupData.HalfSizePickUp);
		Pickup* pickup = static_cast<Pickup*>(pickupG);
		pickup->SetPointValue(pickupData.pointValue);
		pickup->SetPickUpID(pickupData.pickupSprite);
		pickup->SetActive(true);
	}
}

void Pickup::Update(GameState& gameState)
{
	SetPosition(GetConstPos());
}

void Pickup::Draw(GameState& gameState) const
{
	Play::DrawSprite(GetPickUpID(), GetPosition() - gameState.camera.pos, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * gameState.time));
}