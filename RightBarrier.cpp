#include "GameObject.h"
#include "RightBarrier.h"

RBarrier::RBarrier(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_RBARRIER);
	SetUpdateOrder(4);
	SetStatic(true);
	this->SetHalfSize({ (ZOOL_SIZE), (LEVEL_HEIGHT / 2) });
}

void RBarrier::Spawn(GameState& state)
{
	// Right barrier constructor
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_RBARRIER) < 1)
	{
		Point2f initialPos = { (LEVEL_WIDTH), (LEVEL_HEIGHT /2) };
		GameObject* rBarrier = new RBarrier(initialPos - state.camera.pos);
	}
}

void RBarrier::Update(GameState& state) 
{

}

void RBarrier::Draw(GameState& state) const {}