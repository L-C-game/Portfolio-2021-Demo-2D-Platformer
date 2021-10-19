#pragma once
#include "Play.h"
#include "GameObject.h"

class Ceiling : public GameObject
{
public:
	Ceiling(Point2f pos);
	~Ceiling() {};

	static void Spawn();

	// Game Object overrides
	void Update(GameState& state) override;
	void Draw(GameState& state) const override;
};