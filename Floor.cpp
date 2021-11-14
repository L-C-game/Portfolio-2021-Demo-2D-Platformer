/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

#include "GameObject.h"
#include "Floor.h"

Floor::Floor(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_FLOOR);
	SetUpdateOrder(updateOrder::UPDATE_ORDER_FLOOR);
	SetDrawOrder(drawOrder::DRAW_ORDER_FLOOR);
	SetHalfSize({(Play::GetSpriteWidth(floorpng) / 2), (Play::GetSpriteHeight(floorpng) / 2)});
	SetConstPos(pos);
}

void Floor::Spawn()
{
	if (GameObject::s_vUpdateList.size() == 0)
	{
		Point2f initialPos = { ((g_LEVEL_WIDTH)/ 2), g_FLOOR_Y };
		GameObject* floor = new Floor(initialPos);
		floor->SetActive(true);
	}
}

void Floor::Update(GameState& gameState)
{
	SetPosition(GetConstPos());
	gameState;
}

void Floor::Draw(GameState& gameState) const
{
	Play::DrawSprite(floorpng, GetPosition() - gameState.camera.pos, static_cast<int>(g_SINGLE_FRAME_ANIM_SPEED * gameState.time));
}