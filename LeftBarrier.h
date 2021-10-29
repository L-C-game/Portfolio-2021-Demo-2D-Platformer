#pragma once
#include "Play.h"
#include "GameObject.h"

class LBarrier : public GameObject
{
public:
	LBarrier(Point2f pos);
	~LBarrier() {};

	static void Spawn(GameState& gameState);

	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;
};