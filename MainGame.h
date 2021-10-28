// Utilities for the main game cpp file
#pragma once
#include "Play.h"

// Important constants
//Screen constants
constexpr float S_PIXELS_PER_UNIT = 16.0f; // Each unit in zool is 16x16
constexpr float S_PIXELS_PER_UNIT_DOUBLE = 32.0f; // 2x a single unit

constexpr int ZOOL_SIZE = 48;

// Resolution constants
constexpr int S_DISPLAY_WIDTH = 640;
constexpr int S_DISPLAY_HEIGHT = 360;
constexpr int S_DISPLAY_SCALE = 2;

constexpr int LEVEL_WIDTH = 1920;
constexpr int LEVEL_HEIGHT = 640;

// Mathematical constants
constexpr double pi = 3.14159265358979323846;

constexpr float QUARTER = 0.25f;
constexpr float THREE_QUARTERS = 0.75f;

// Sprite ID's
const enum spriteIdInts
{
	nullpng = -1,
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
constexpr float GRAVITY = (20.0f / 60.0f); // Acceleration due to gravity
constexpr float MOVEACC = (45.0f / 60.0f); // Acceleration when moving

constexpr int MAX_SPEED_RUN = 5; // Maximum horizontal speed
constexpr int MAX_SPEED_FALL = 7; // Maximum vertical speed

constexpr float MINIMUM_SPEED_RUN = 0.5f; // A minimum speed, when this is reached the player stops and changes to idle

// The excess pixels on the zool sprites
constexpr int PIXEL_EXCESS_X_ZOOL = 10;
constexpr int PIXEL_EXCESS_Y_ZOOL = 8;

constexpr int PIXEL_BUFFER = 2;

// Run animation speed
constexpr int RUN_ANIM_SPEED = 32;
constexpr int SINGLE_FRAME_ANIM_SPEED = 1;

//Platform data and functions to populate world with platforms
constexpr float halfSizeXPlat = 24.0f;
constexpr float halfSizeYPlat = (S_PIXELS_PER_UNIT / 2) + PIXEL_BUFFER;

constexpr int platformAmount = 4;

const Point2f initialPlayerPos = { static_cast<float>(S_DISPLAY_WIDTH/2), static_cast<float>(S_DISPLAY_HEIGHT/2) };

// Camera struct 
struct Camera
{
	Point2f pos{ 0.0f, 0.0f };
	const float width{ S_DISPLAY_WIDTH };
	const float height{ S_DISPLAY_HEIGHT };
};

// Using a struct as the base access is public
struct GameState
{
	// The time elapsed in the game
	float time{ 0.0f };
	Camera camera;
};

struct PlatformData
{
	Point2f pos{0.0f, 0.0f};
	Point2f HalfSizePlat{ halfSizeXPlat, halfSizeYPlat };
	spriteIdInts colour{nullpng};
};


