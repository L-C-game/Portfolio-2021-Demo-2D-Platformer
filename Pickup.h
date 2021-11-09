/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

#pragma once
#include"Play.h"
#include "GameObject.h"

class Pickup : public GameObject
{
public:
	Pickup(Point2f pos);

	~Pickup() 
	{
		SetActive(false);
	};

	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;

	static void Spawn(PickUpData& pickupData);

	void SetConstPos(Point2f constPos) { m_constPos = constPos; }
	Point2f GetConstPos() const { return m_constPos; }

	void SetPointValue(int pointValue) { m_pointValue = pointValue; }
	int GetPointValue() const { return m_pointValue; }

	void SetPickUpID(int pickupID) { m_pickupID = pickupID; }
	int GetPickUpID() const { return m_pickupID; }

private:
	Point2f m_constPos{ 0.0f, 0.0f };
	int m_pointValue{ 0 };
	int m_pickupID{ 0 };
};

