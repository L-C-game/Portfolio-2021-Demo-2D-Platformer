#pragma once
#include "Play.h"
#include "GameObject.h"

class RBarrier : public GameObject
{
public:
	RBarrier(Point2f pos);
	~RBarrier() {};

	static void Spawn(GameState& state);

	// Game Object overrides
	void Update(GameState& state) override;
	void Draw(GameState& state) const override;
};
