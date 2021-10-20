#include "GameObject.h"
#include "Platform.h"

Platform::Platform(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_PLATFORM);
	SetUpdateOrder(4);
	SetDrawOrder(4);
	SetStatic(true);
}

void Platform::Spawn()
{
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_PLATFORM) < 1)
	{
		Point2f initialPos = { (S_DISPLAY_WIDTH / 2), (S_DISPLAY_HEIGHT - (2.0f * S_SCREEN_LIMIT)) };
		GameObject* platformBlue = new Platform(initialPos);
		platformBlue->SetCurrentSpriteId(Play::GetSpriteId("spr_platform_blue"));
		platformBlue->SetHalfSize({ (Play::GetSpriteWidth(platformBlue->GetCurrentSpriteId()) / 2), (Play::GetSpriteHeight(platformBlue->GetCurrentSpriteId()) / 2) });
	}
}

void Platform::Update(GameState& state){}

void Platform::Draw(GameState& state) const
{
	Play::DrawSprite(this->GetCurrentSpriteId(), this->GetPosition(), static_cast<int>(1 * state.time));
}