#include "GameObject.h"
#include "Floor.h"

Floor::Floor(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_FLOOR);
	SetUpdateOrder(1);
	SetDrawOrder(1);
	SetStatic(true);
	this->SetHalfSize({(Play::GetSpriteWidth(floorpng) / 2), (Play::GetSpriteHeight(floorpng) / 2)});
	SetConstPos(pos);
}


void Floor::Spawn()
{
	if (GameObject::s_vUpdateList.size() == 0)
	{
		// Floor constructor
		if (GameObject::GetObjectCount(GameObject::Type::OBJ_FLOOR) < 1)
		{
			Point2f initialPos = { ((LEVEL_WIDTH)/ 2), (S_DISPLAY_HEIGHT + ZOOL_SIZE) };
			GameObject* floor = new Floor(initialPos);
		}
	}
}

void Floor::Update(GameState& state)
{
	Point2f transformPos = { this->GetConstPos().x, this->GetConstPos().y - state.camera.pos.y };
	this->SetPosition(transformPos);
}

void Floor::Draw(GameState& state) const
{
	Play::DrawSprite(floorpng, this->GetPosition() - state.camera.pos, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
}