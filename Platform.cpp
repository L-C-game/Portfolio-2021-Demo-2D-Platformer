/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

#include "GameObject.h"
#include "Platform.h"

Platform::Platform(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_PLATFORM);
	SetUpdateOrder(updateOrder::UPDATE_ORDER_PLATFORM);
	SetDrawOrder(drawOrder::DRAW_ORDER_PLATFORM);
	SetConstPos(pos);
}

void Platform::Spawn(PlatformData& platData)
{
	GameObject* platformG = new Platform(platData.pos);
	platformG->SetHalfSize( platData.HalfSizePlat );
	Platform* platform = static_cast<Platform*>(platformG);
	platform->SetPlatID(platData.colour);
	platform->SetActive(true);
}

void Platform::Update(GameState& gameState)
{
	SetPosition(GetConstPos());
	gameState;
}

void Platform::Draw(GameState& gameState) const
{
	Play::DrawSprite(GetPlatID(), GetPosition() - gameState.camera.pos, static_cast<int>(g_SINGLE_FRAME_ANIM_SPEED * gameState.time));
}