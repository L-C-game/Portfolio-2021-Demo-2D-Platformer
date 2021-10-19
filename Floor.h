#pragma once
#include "Play.h"
#include "GameObject.h"

class Floor : public GameObject
{
public: 
	Floor(Point2f pos);
	~Floor() {};

	static void Spawn();

	// Game Object overrides
	void Update(GameState& state) override;
	void Draw(GameState& state) const override;
};
