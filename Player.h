#pragma once
#include "Play.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(Point2f pos)
	{
		SetType(Type::OBJ_PLAYER);
		SetUpdateOrder(0);
		SetDrawOrder(0);
	}

	~Player() {}

	void Update(GameState& state) override;
};