// Utilities for the main game cpp file
#pragma once
#include "Play.h"

// Using a struct as the base access is public
struct GameState
{
	float time{ 0 };
};

// Important constants
// Used in the HasCollided function
constexpr int S_SCREEN_LIMIT = 24;
constexpr int S_HALF_LIMIT = 12;
// Resolution based on the SNES
constexpr int S_DISPLAY_WIDTH = 256;
constexpr int S_DISPLAY_HEIGHT = 224;
constexpr int S_DISPLAY_SCALE = 4;
// Mathematical constants
const double pi = 3.14159265358979323846;