#pragma once
#include "Play.h"
#include "GameObject.h"

class Platform : public GameObject
{
public:
	Platform(Point2f pos);
	~Platform() {};

	static void Spawn();

	// Game Object overrides
	void Update(GameState& state) override;
	void Draw(GameState& state) const override;

//	enum class Colour
//	{
//		COLOUR_NULL = -1,
//		COLOUR_BLUE = 0,
//		COLOUR_RED = 1,
//		COLOUR_GREEN = 2,
//		COLOUR_YELLOW =3,
//	};
//
//	// Getters and setters for the colour of the block
//	void SetColour(Colour colour) { m_colour = colour; }
//	Colour GetColour() const { return m_colour; };
//
//protected:
//	Colour m_colour{ Colour::COLOUR_BLUE };
};