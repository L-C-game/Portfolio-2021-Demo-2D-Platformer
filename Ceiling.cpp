#include "GameObject.h"
#include "Ceiling.h"

Ceiling::Ceiling(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_CEILING);
	SetUpdateOrder(updateOrder::UPDATE_ORDER_CEILING);
	SetStatic(true);
	this->SetHalfSize({ (S_DISPLAY_WIDTH/2), (S_PIXELS_PER_UNIT) });
}

void Ceiling::Spawn(GameState& gameState)
{
	// Floor constructor
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_CEILING) < 1)
	{
		Point2f initialPos = { (S_DISPLAY_WIDTH / 2), -ZOOL_SIZE };
		GameObject* ceiling = new Ceiling(initialPos - gameState.camera.pos);
		ceiling->SetActive(true);
	}
}

void Ceiling::Update(GameState& gameState)
{

}

void Ceiling::Draw(GameState& gameState) const
{

}