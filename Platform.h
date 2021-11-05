#pragma once
#include "Play.h"
#include "GameObject.h"

class Platform : public GameObject
{
public:
	Platform(Point2f pos);
	~Platform() 
	{
		SetActive(false);
	};

	static void Spawn(PlatformData& platData);

	// Game Object overrides
	void Update(GameState& gameState) override;
	void Draw(GameState& gameState) const override;

	void SetConstPos(Point2f constPos) { m_constPos = constPos; }
	Point2f GetConstPos() const { return m_constPos; }

	void SetPlatID(int platID) { m_platID = platID; }
	int GetPlatID() const { return m_platID; }

private:
	Point2f m_constPos{ 0.0f, 0.0f };
	int m_platID{ 0 };
};