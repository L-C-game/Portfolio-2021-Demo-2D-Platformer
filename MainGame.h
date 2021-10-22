// Utilities for the main game cpp file
#pragma once
#include "Play.h"

// Using a struct as the base access is public
struct GameState
{
	float time{ 0.0f };
};

// Important constants
//Screen constants
constexpr float S_PIXELS_PER_UNIT = 16.0f; // Each unit in zool is 16x16
constexpr float S_PIXELS_PER_UNIT_DOUBLE = 32.0f; // 2x a single unit

// Resolution constants
constexpr int S_DISPLAY_WIDTH = 640;
constexpr int S_DISPLAY_HEIGHT = 360;
constexpr int S_DISPLAY_SCALE = 2;

// Mathematical constants
const double pi = 3.14159265358979323846;

const float QUARTER = 0.25f;
const float THREE_QUARTERS = 0.75f;

// Sprite ID's
const enum spriteIdInts
{
	floorpng = 0,
	platBluepng,
	platGreenpng,
	platRedpng,
	platYellowpng,
	zoolCrouchLpng,
	zoolCrouchRpng,
	zoolFallLpng,
	zoolFallRpng,
	zoolJumpLpng,
	zoolJumpRpng,
	zoolSkidLpng,
	zoolSkidRpng,
	zoolSlideLpng,
	zoolSlideRpng,
	zoolIdleLpng,
	zoolIdleRpng,
	zoolWalkLpng,
	zoolWalkRpng,
};

// Movement constants
const float GRAVITY = (15.0f / 60.0f); // Acceleration due to gravity
const float MOVEACC = (12.0f / 60.0f); // Acceleration when moving

const int MAX_SPEED_RUN = 3; // Maximum horizontal speed
const int MAX_SPEED_FALL = 6; // Maximum vertical speed

const float MINIMUM_SPEED_RUN = 0.1f; // A minimum speed, when this is reached the player stops and changes to idle

// The excess pixels on the zool sprites
const int PIXEL_EXCESS_X_ZOOL = 10;
const int PIXEL_EXCESS_Y_ZOOL = 8;

const int PIXEL_BUFFER = 2;

// Run animation speed
const int RUN_ANIM_SPEED = 32;
const int SINGLE_FRAME_ANIM_SPEED = 1;

//Platform data and functions to populate world with platforms
const float halfSizeXPlat = 24.0f;
const float halfSizeYPlat = (S_PIXELS_PER_UNIT / 2) + PIXEL_BUFFER;

const int platformAmount = 4;

struct PlatformData
{
	Point2f pos;
	Point2f HalfSizePlat{ halfSizeXPlat, halfSizeYPlat };
	spriteIdInts colour;
};
