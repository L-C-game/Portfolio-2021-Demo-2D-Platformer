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
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_PLATFORM) < 5)
	{
		GameObject* platformG = new Platform(platData.pos);
		platformG->SetHalfSize( platData.HalfSizePlat );
		Platform* platform = static_cast<Platform*>(platformG);
		platform->SetPlatID(platData.colour);
	}
}

void Platform::Update(GameState& state)
{
	this->SetPosition(this->GetConstPos() - state.camera.pos);
}

void Platform::Draw(GameState& state) const
{
	Play::DrawSprite(this->GetPlatID(), this->GetPosition() - state.camera.pos, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
}