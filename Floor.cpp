#include "GameObject.h"
#include "Floor.h"

Floor::Floor(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_FLOOR);
	SetUpdateOrder(1);
	SetDrawOrder(1);
	SetStatic(true);
	SetHalfSize({(Play::GetSpriteWidth(floorpng) / 2), (Play::GetSpriteHeight(floorpng) / 2)});
	SetConstPos(pos);
}


void Floor::Spawn()
{
	if (GameObject::s_vUpdateList.size() == 0)
	{
		// Floor constructor
		if (GameObject::GetObjectCount(GameObject::Type::OBJ_FLOOR) < 1)
		{
			Point2f initialPos = { ((LEVEL_WIDTH)/ 2), FLOOR_Y };
			GameObject* floor = new Floor(initialPos);
			floor->SetActive(true);
		}
	}
}

void Floor::Update(GameState& gameState)
{
	SetPosition(GetConstPos());
}

void Floor::Draw(GameState& gameState) const
{
	Play::DrawSprite(floorpng, GetPosition() - gameState.camera.pos, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * gameState.time));
}