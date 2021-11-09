/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game

	Left world barrier
*/

#pragma once
#include "Play.h"
#include "GameObject.h"

class LBarrier : public GameObject
{
public:
	LBarrier(Point2f pos);
	~LBarrier() 
	{
		SetActive(false);
	};

	static void Spawn(GameState& gameState);

	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;
};