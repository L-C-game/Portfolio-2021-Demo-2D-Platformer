#include "GameObject.h"
#include "Platform.h"

Platform::Platform(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_PLATFORM);
	SetUpdateOrder(4);
	SetDrawOrder(4);
	SetStatic(true);
}

void Platform::Spawn(PlatformData& platData)
{
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_PLATFORM) < 5)
	{
		GameObject* platform = new Platform(platData.pos);
		platform->SetCurrentSpriteId(platData.colour);
		platform->SetHalfSize( platData.HalfSizePlat );
	}
}

void Platform::Update(GameState& state){}

void Platform::Draw(GameState& state) const
{
	Play::DrawSprite(this->GetCurrentSpriteId(), this->GetPosition(), static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
}