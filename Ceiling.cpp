#include "GameObject.h"
#include "Ceiling.h"

Ceiling::Ceiling(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_CEILING);
	SetUpdateOrder(3);
	SetDrawOrder(3);
	SetStatic(true);
	this->SetHalfSize({ (S_DISPLAY_WIDTH/2), (S_PIXELS_PER_UNIT) });
}

void Ceiling::Spawn(GameState& state)
{
	// Floor constructor
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_CEILING) < 1)
	{
		Point2f initialPos = { (S_DISPLAY_WIDTH / 2), -S_PIXELS_PER_UNIT };
		GameObject* ceiling = new Ceiling(initialPos - state.camera.pos);

	}
}

void Ceiling::Update(GameState& state)
{

}

void Ceiling::Draw(GameState& state) const
{

}