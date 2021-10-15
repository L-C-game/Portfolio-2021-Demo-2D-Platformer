// Utilities for the main game cpp file
#pragma once
#include "Play.h"

// Using a struct as the base access is public
struct GameState
{
	float time{ 0 };
};

// Important constants
constexpr float S_SCREEN_LIMIT = 32.0f;
constexpr float S_HALF_LIMIT = 16.0f;

// Resolution based on the Amiga
constexpr int S_DISPLAY_WIDTH = 640;
constexpr int S_DISPLAY_HEIGHT = 360;
constexpr int S_DISPLAY_SCALE = 2;
// Mathematical constants
const double pi = 3.14159265358979323846;

const float GRAVITY = (4.0f / 60.0f);

const float PIXEL_BUFFER = 2.0f;
const float MAX_SPEED_RUN = 10.0f;
const float MAX_SPEED_FALL = 20.0f;