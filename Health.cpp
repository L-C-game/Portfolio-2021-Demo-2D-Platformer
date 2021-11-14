#include "GameObject.h"
#include "Health.h"

Health::Health(Point2f pos) : GameObject(pos)
{
	SetType(GameObject::Type::OBJ_HEALTH);
	SetUpdateOrder(UPDATE_ORDER_HEALTH);
	SetDrawOrder(DRAW_ORDER_HEALTH);
	SetConstPos(pos);
	SetIsCollectable(true);
	SetSolid(false);
}

void Health::Spawn(HealthData& healthData)
{
	GameObject* health = new Health(healthData.pos);
	health->SetHalfSize({ g_HALF_SIZE_SMALL_OBJ, g_HALF_SIZE_SMALL_OBJ });
}

void Health::Update(GameState& gameState)
{
	SetPosition(GetConstPos());
	gameState;
}

void Health::Draw(GameState& gameState) const
{
	Play::DrawSprite(GetHealthID(), GetPosition() - gameState.camera.pos, static_cast<int>( g_TWO_FRAME_ANIM_SPEED * gameState.time));
}
