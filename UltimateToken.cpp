#include "UltimateToken.h"

UltimateToken::UltimateToken(Point2f pos) : GameObject(pos)
{
	SetType(GameObject::Type::OBJ_ULTIMATE);
	SetUpdateOrder(UPDATE_ORDER_ULTIMATE);
	SetDrawOrder(DRAW_ORDER_ULTIMATE);
	SetConstPos(pos);
	SetIsCollectable(true);
	SetSolid(false);
}

void UltimateToken::Spawn()
{
	GameObject* ultimateToken = new UltimateToken({ 640, 898 });
	ultimateToken->SetHalfSize({ g_PIXELS_PER_UNIT, g_PIXELS_PER_UNIT });
}

void UltimateToken::Update(GameState& gameState)
{
	SetPosition(GetConstPos());
	gameState;
}

void UltimateToken::Draw(GameState& gameState) const
{
	Play::DrawSprite(GetUltimateTokenID(), GetPosition() - gameState.camera.pos, static_cast<int>(g_SINGLE_FRAME_ANIM_SPEED * gameState.time));
}
