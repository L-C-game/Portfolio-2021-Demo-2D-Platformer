#include "GameObject.h"
#include "Spike.h"

Spike::Spike(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_SPIKE);
	SetUpdateOrder(8);
	SetDrawOrder(8);
	SetStatic(true);
	SetConstPos(pos);
}

void Spike::Spawn(SpikeData& platData)
{
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_SPIKE) < (SPIKE_AMOUNT))
	{
		GameObject* spikeG = new Spike(platData.pos);
		spikeG->SetHalfSize(platData.HalfSizeSpike);
		spikeG->SetActive(true);
	}
}

void Spike::Update(GameState& gameState)
{
	SetPosition(GetConstPos());
}

void Spike::Draw(GameState& gameState) const
{
	Play::DrawSprite(spikespng, GetPosition() - gameState.camera.pos, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * gameState.time));
}
