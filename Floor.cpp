#include "GameObject.h"
#include "Floor.h"

Floor::Floor(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_FLOOR);
	SetUpdateOrder(1);
	SetDrawOrder(1);
	SetStatic(true);
	this->SetCurrentSpriteId(Play::GetSpriteId("spr_floor"));
	this->SetHalfSize({(Play::GetSpriteWidth(this->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER, (Play::GetSpriteHeight(this->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER });
}

void Floor::Spawn(GameState& state)
{
	if (GameObject::s_vUpdateList.size() == 0)
	{
		// Floor constructor
		if (GameObject::GetObjectCount(GameObject::Type::OBJ_FLOOR) < 1)
		{
			Point2f initialPos = { (S_DISPLAY_WIDTH/2), (S_DISPLAY_HEIGHT - S_HALF_LIMIT) };
			GameObject* floor = new Floor(initialPos);

		}
	}
}

void Floor::Update(GameState& state)
{

}

void Floor::Draw(GameState& state) const
{
	Play::DrawSprite(this->GetCurrentSpriteId(), this->GetPosition(), static_cast<int>(1 * state.time));
}