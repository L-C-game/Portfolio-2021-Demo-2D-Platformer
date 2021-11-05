#include "GameObject.h"
#include "Platform.h"

Platform::Platform(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_PLATFORM);
	SetUpdateOrder(5);
	SetDrawOrder(5);
	SetStatic(true);
	SetConstPos(pos);
}

void Platform::Spawn(PlatformData& platData)
{
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_PLATFORM) < (PLATFORM_AMOUNT))
	{
		GameObject* platformG = new Platform(platData.pos);
		platformG->SetHalfSize( platData.HalfSizePlat );
		Platform* platform = static_cast<Platform*>(platformG);
		platform->SetPlatID(platData.colour);
		platform->SetActive(true);
	}
}

void Platform::Update(GameState& gameState)
{
	SetPosition(GetConstPos());
}

void Platform::Draw(GameState& gameState) const
{
	Play::DrawSprite(GetPlatID(), GetPosition() - gameState.camera.pos, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * gameState.time));
}