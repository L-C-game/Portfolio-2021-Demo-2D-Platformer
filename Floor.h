#pragma once
#include "Play.h"
#include "GameObject.h"

class Floor : public GameObject
{
public: 
	Floor(Point2f pos);
	~Floor() {};

	static void Spawn();

	// Game Object overrides
	void Update(GameState& state) override;
	void Draw(GameState& state) const override;

	void SetConstPos(Point2f constPos) { m_constPos = constPos; }
	Point2f GetConstPos() const { return m_constPos; }

private:
	Point2f m_constPos{ 0.0f, 0.0f};
};
