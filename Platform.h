#pragma once
#include "Play.h"
#include "GameObject.h"

class Platform : public GameObject
{
public:
	Platform(Point2f pos);
	~Platform() {};

	static void Spawn(PlatformData& platData);

	// Game Object overrides
	void Update(GameState& state) override;
	void Draw(GameState& state) const override;
};