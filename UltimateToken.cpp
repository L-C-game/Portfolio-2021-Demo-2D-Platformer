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
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_ULTIMATE) < 1)
	{
		GameObject* ultimateToken = new UltimateToken({ (S_DISPLAY_WIDTH * THREE_QUARTERS + 2 * S_DISPLAY_WIDTH + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (2 * ZOOL_SIZE) - S_PIXELS_PER_UNIT_DOUBLE) });
		ultimateToken->SetHalfSize({ S_PIXELS_PER_UNIT_DOUBLE - 1, S_PIXELS_PER_UNIT_DOUBLE - 1 });
	}
}

void UltimateToken::Update(GameState& gameState)
{
	SetPosition(GetConstPos());
}

void UltimateToken::Draw(GameState& gameState) const
{
	Play::DrawSprite(GetUltimateTokenID(), GetPosition() - gameState.camera.pos, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * gameState.time));
}
