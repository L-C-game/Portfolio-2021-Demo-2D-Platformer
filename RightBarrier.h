#pragma once
#include "Play.h"
#include "GameObject.h"

class RBarrier : public GameObject
{
public:
	RBarrier(Point2f pos);
	~RBarrier() {};

	static void Spawn(GameState& gameState);

	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;
};
