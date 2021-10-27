#pragma once
#include "Play.h"
#include "GameObject.h"

class LBarrier : public GameObject
{
public:
	LBarrier(Point2f pos);
	~LBarrier() {};

	static void Spawn(GameState& state);

	// Game Object overrides
	void Update(GameState& state) override;
	void Draw(GameState& state) const override;
};