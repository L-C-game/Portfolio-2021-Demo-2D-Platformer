/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

#include "GameObject.h"
#include "Spike.h"

Spike::Spike(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_SPIKE);
	SetUpdateOrder(updateOrder::UPDATE_ORDER_SPIKE);
	SetDrawOrder(drawOrder::DRAW_ORDER_SPIKE);
	SetConstPos(pos);
}

void Spike::Spawn(SpikeData& platData)
{
	GameObject* spikeG = new Spike(platData.pos);
	spikeG->SetHalfSize(platData.HalfSizeSpike);
	spikeG->SetActive(true);
}

void Spike::Update(GameState& gameState)
{
	SetPosition(GetConstPos());
	gameState;
}

void Spike::Draw(GameState& gameState) const
{
	Play::DrawSprite(spikespng, GetPosition() - gameState.camera.pos, static_cast<int>(g_SINGLE_FRAME_ANIM_SPEED * gameState.time));
}
