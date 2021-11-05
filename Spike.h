#pragma once
#include "GameObject.h"

class Spike :public GameObject
{
public:
	Spike(Point2f pos);
	~Spike() 
	{
		SetActive(false);
	};

	static void Spawn(SpikeData& spikeData);

	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;

	void SetConstPos(Point2f constPos) { m_constPos = constPos; }
	Point2f GetConstPos() const { return m_constPos; }

private:
	Point2f m_constPos{ 0.0f, 0.0f };
};
