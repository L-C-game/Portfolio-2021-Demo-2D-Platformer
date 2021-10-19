#include "GameObject.h"
#include "Ceiling.h"

Ceiling::Ceiling(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_CEILING);
	SetUpdateOrder(3);
	SetDrawOrder(3);
	SetStatic(true);
	this->SetHalfSize({ (S_DISPLAY_WIDTH/2), (S_HALF_LIMIT) });
}

void Ceiling::Spawn()
{
	// Floor constructor
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_CEILING) < 1)
	{
		Point2f initialPos = { (S_DISPLAY_WIDTH / 2), -S_HALF_LIMIT };
		GameObject* ceiling = new Ceiling(initialPos);

	}
}

void Ceiling::Update(GameState& state)
{

}

void Ceiling::Draw(GameState& state) const
{

}