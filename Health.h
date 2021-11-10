#pragma once
#include "GameObject.h"

class Health :public GameObject
{
public:
	Health(Point2f pos);
	~Health() 
	{ 
		SetActive(false); 
	};

	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;

	static void Spawn(HealthData& healthData);

	void SetConstPos(Point2f constPos) { m_constPos = constPos; }
	Point2f GetConstPos() const { return m_constPos; }

	int GetHealthID() const { return m_healthID; }

private:
	Point2f m_constPos{ 0.0f, 0.0f };
	int m_healthID{healthpng};
};

