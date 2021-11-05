#pragma once
#include "Play.h"
#include "GameObject.h"

class Ceiling : public GameObject
{
public:
	Ceiling(Point2f pos);
	~Ceiling() 
	{
		SetActive(false);
	};

	static void Spawn(GameState& gameState);

	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;
};