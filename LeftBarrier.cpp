#include "GameObject.h"
#include "LeftBarrier.h"

LBarrier::LBarrier(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_LBARRIER);
	SetUpdateOrder(2);
	SetStatic(true);
	this->SetHalfSize({(ZOOL_SIZE), (LEVEL_HEIGHT/2)});
}

void LBarrier::Spawn(GameState& state)
{
	// Left barrier constructor
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_LBARRIER) < 1)
	{
		Point2f initialPos = { -(ZOOL_SIZE), (LEVEL_HEIGHT/2) };
		GameObject* lBarrier = new LBarrier(initialPos - state.camera.pos);
	}
}

void LBarrier::Update(GameState& state) {}

void LBarrier::Draw(GameState& state) const {}