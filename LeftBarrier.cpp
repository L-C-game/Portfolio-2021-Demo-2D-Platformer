#include "GameObject.h"
#include "LeftBarrier.h"

LBarrier::LBarrier(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_LBARRIER);
	SetUpdateOrder(2);
	SetDrawOrder(2);
	SetStatic(true);
	this->SetHalfSize({(S_PIXELS_PER_UNIT), (S_DISPLAY_HEIGHT/2)});
}

void LBarrier::Spawn()
{
	// Left barrier constructor
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_LBARRIER) < 1)
	{
		Point2f initialPos = { -(S_PIXELS_PER_UNIT), (S_DISPLAY_HEIGHT/2) };
		GameObject* lBarrier = new LBarrier(initialPos);
	}
}

void LBarrier::Update(GameState& state) {}

void LBarrier::Draw(GameState& state) const {}