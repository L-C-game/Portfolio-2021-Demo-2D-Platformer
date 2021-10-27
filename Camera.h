#pragma once
#include "Play.h"
#include "GameObject.h"
// Camera object header

class Camera : public GameObject
{
public: 
	Camera(Point2f pos);
	~Camera() {};

	static void Spawn();

	// Game Object overrides
	void Update(GameState& state) override;
	void Draw(GameState& state) const override;

private:
};

