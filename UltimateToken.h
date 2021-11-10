#pragma once
#include "GameObject.h"
class UltimateToken :public GameObject
{
public:
	UltimateToken(Point2f pos);
	~UltimateToken()
	{
		SetActive(false);
	};

	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;

	static void Spawn();

	void SetConstPos(Point2f constPos) { m_constPos = constPos; }
	Point2f GetConstPos() const { return m_constPos; }

	int GetUltimateTokenID() const { return m_ultimateTokenID; }

private:
	Point2f m_constPos{ 0.0f, 0.0f };
	int m_ultimateTokenID{ ultimateTokenpng };
};

