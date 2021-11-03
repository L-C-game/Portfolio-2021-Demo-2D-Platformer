// Utilities for the main game cpp file
#pragma once
#include "Play.h"

// Important constants
//Screen constants
constexpr int S_PIXELS_PER_UNIT{ 16 }; // Each unit in zool is 16x16
constexpr int S_PIXELS_PER_UNIT_DOUBLE{ 32 }; // 2x a single unit

constexpr int ZOOL_SIZE{ 48 };

// Resolution constants
constexpr int S_DISPLAY_WIDTH{ 640 };
constexpr int S_DISPLAY_HEIGHT{ 360 };
constexpr int S_DISPLAY_SCALE{ 2 };

constexpr int LEVEL_WIDTH{ 1920 };
constexpr int LEVEL_HEIGHT{ 1080 };

// Floor position, for placing platforms wrt the floor
constexpr int FLOOR_Y = (LEVEL_HEIGHT - S_PIXELS_PER_UNIT_DOUBLE);

// Mathematical constants
constexpr double pi{ 3.14159265358979323846 };

// These constants are useful for the placements of items and platforms
constexpr float QUARTER{ 0.25f };
constexpr float THREE_QUARTERS{ 0.75f };
constexpr float THIRD{ 1 / 3 };
constexpr float TENTH{ 0.1f };
constexpr float FIFTH{ 0.2f };
constexpr float THREE_TENTHS{ 0.3f };
constexpr float TWO_FIFTHS{ 0.4f };
constexpr float THREE_FIFTHS{ 0.6f };
constexpr float SEVEN_TENTHS{ 0.7f};
constexpr float FOUR_FIFTHS{ 0.8f };
constexpr float NINE_TENTHS{ 0.9f };

// Sprite ID's
const enum spriteIdInts
{
	nullpng = -1,
	fontMedpng,
	fontBigpng,
	fivepointpng,
	floorpng,
	healthpng,
	halfhealth,
	blockbreakpng,
	blockpng,
	platBluepng,
	platGreenpng,
	platPinkpng,
	platRedpng,
	platSpecialpng,
	platYellowpng,
	spikespng,
	tenpointpng,
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

const enum updateOrder
{
	FLOOR_UPDATE = 8,
	PLAYER_UPDATE = 7,
	LBARRIER_UPDATE = 6,
	CEILING_UPDATE = 5,
	RBARRIER_UPDATE = 4,
	PLATFORM_UPDATE = 3,
	PICKUP_UPDATE = 2,
	BLOCK_UPDATE = 1,
	SPIKE_UPDATE = 0,
};

// Movement constants
constexpr float GRAVITY{ (30.0f / 60.0f) }; // Acceleration due to gravity
constexpr float MOVE_ACC{ (45.0f / 60.0f) }; // Acceleration when moving
constexpr float STUN_ACC{(90.0f / 60.0f)};
constexpr int JUMP_SPEED{ 4 }; // The speed of Jumping upwards
// Maximum jump duration in seconds
constexpr int JUMP_DURATION{ 30 };
constexpr int I_FRAMES_DURATION{ 15 };
constexpr int BLINK_DURATION{ 3 };

// Min and max speed constants
constexpr float MAX_SPEED_RUN{ 3.5 }; // Maximum horizontal speed
constexpr int MAX_SPEED_FALL{ 7 }; // Maximum vertical speed (can fall faster than he can run)
constexpr float MINIMUM_SPEED_RUN{ 0.25f }; // A minimum speed, when this is reached the player stops and changes to idle

// The excess pixels on the zool sprites
constexpr int PIXEL_EXCESS_X_ZOOL{ 10 };
constexpr int PIXEL_EXCESS_Y_ZOOL{ 8 };

constexpr int PIXEL_BUFFER{ 2 };

// Run animation speed
constexpr int RUN_ANIM_SPEED{ 32 };
constexpr int SINGLE_FRAME_ANIM_SPEED{ 1 };
constexpr int BLOCK_BREAK_ANIM_SPEED{ 12 };

//Platform data and functions to populate world with platforms
constexpr float HALF_SIZE_PLAT_X{ 24.0f };
constexpr float HALF_SIZE_PLAT_Y{ 10.0f };

constexpr float HALF_SIZE_SMALL_OBJ{ 8.0f };

constexpr int PLATFORM_AMOUNT{ 6 };

constexpr int PICKUP_AMOUNT{ 4 };
constexpr int FIVE_POINTS{ 5 };
constexpr int TEN_POINTS{ 10 };

constexpr int BLOCK_AMOUNT{ 1 };
constexpr int BLOCK_DURATION{ 30 };

constexpr int SPIKE_AMOUNT{ 1 };

const Point2f initialPlayerPos = { static_cast<float>(S_DISPLAY_WIDTH * THIRD), static_cast<float>(LEVEL_HEIGHT - 2 * ZOOL_SIZE) } ;
constexpr int MAX_HEALTH_PLAYER{ 6 };
constexpr int MIN_HEALTH_PLAYER{ 1 };

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
	int score{ 0 };
	int health{ 0 };
	Camera camera;
};

struct PlatformData
{
	Point2f pos{0.0f, 0.0f};
	Point2f HalfSizePlat{ HALF_SIZE_PLAT_X, HALF_SIZE_PLAT_Y };
	spriteIdInts colour{nullpng};
};

struct PickUpData
{
	Point2f pos{ 0.0f, 0.0f };
	Point2f HalfSizePickUp{ HALF_SIZE_SMALL_OBJ, HALF_SIZE_SMALL_OBJ };
	spriteIdInts pickupSprite{ nullpng };
	int pointValue{ 0 };
};

struct BlockData
{
	Point2f pos{ 0.0f, 0.0f };
	Point2f HalfSizeBlock{ HALF_SIZE_SMALL_OBJ, HALF_SIZE_SMALL_OBJ };
	spriteIdInts blockSprite{ nullpng };
};

struct SpikeData
{
	Point2f pos{ 0.0f, 0.0f };
	Point2f HalfSizeSpike{ HALF_SIZE_SMALL_OBJ, HALF_SIZE_SMALL_OBJ };
};
