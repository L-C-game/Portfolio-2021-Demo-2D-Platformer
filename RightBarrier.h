/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game

	Right world barrier
*/

#pragma once
#include "Play.h"
#include "GameObject.h"

class RBarrier : public GameObject
{
public:
	RBarrier(Point2f pos);
	~RBarrier() 
	{
		SetActive(false);
	};

	static void Spawn(GameState& gameState);

	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;
};
