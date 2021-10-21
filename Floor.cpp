#include "GameObject.h"
#include "Floor.h"

Floor::Floor(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_FLOOR);
	SetUpdateOrder(1);
	SetDrawOrder(1);
	SetStatic(true);
	this->SetCurrentSpriteId(floorpng);
	this->SetHalfSize({(Play::GetSpriteWidth(this->GetCurrentSpriteId()) / 2), (Play::GetSpriteHeight(this->GetCurrentSpriteId()) / 2)});
}

void Floor::Spawn()
{
	if (GameObject::s_vUpdateList.size() == 0)
	{
		// Floor constructor
		if (GameObject::GetObjectCount(GameObject::Type::OBJ_FLOOR) < 1)
		{
			Point2f initialPos = { (S_DISPLAY_WIDTH/2), (S_DISPLAY_HEIGHT - S_PIXELS_PER_UNIT) };
			GameObject* floor = new Floor(initialPos);
		}
	}
}

void Floor::Update(GameState& state)
{

}

void Floor::Draw(GameState& state) const
{
	Play::DrawSprite(this->GetCurrentSpriteId(), this->GetPosition(), static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
}