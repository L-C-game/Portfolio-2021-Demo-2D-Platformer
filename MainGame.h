/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game

	This .h file contains important constants used throughout the game,
	functions that are used in the .cpp file and structs to represent
	certain game objects, 
*/

// Utilities for the main game cpp file
#pragma once
#include "Play.h"

//Screen constants
static constexpr int g_PIXELS_PER_UNIT{ 16 }; // Each unit in zool is 16x16
static constexpr int g_PIXELS_PER_UNIT_DOUBLE{ 32 }; // 2x a single unit

static constexpr int g_ZOOL_SIZE{ 48 };

// Resolution constants
static constexpr int g_DISPLAY_WIDTH{ 640 };
static constexpr int g_DISPLAY_HEIGHT{ 360 };
static constexpr int g_DISPLAY_SCALE{ 2 };

static constexpr int g_LEVEL_WIDTH{ 1920 };
static constexpr int g_LEVEL_HEIGHT{ 1080 };

// Floor position, for placing platforms wrt the floor
static constexpr int g_FLOOR_Y = (g_LEVEL_HEIGHT - g_PIXELS_PER_UNIT_DOUBLE);

// Mathematical constants
static constexpr double g_pi{ 3.14159265358979323846 };

// These constants are useful for the placements of items and platforms
static constexpr float g_QUARTER{ 0.25f };
static constexpr float g_THREE_QUARTERS{ 0.75f };
static constexpr float g_THIRD{ 0.333333333333f };
static constexpr float g_TENTH{ 0.1f };
static constexpr float g_FIFTH{ 0.2f };
static constexpr float g_THREE_TENTHS{ 0.3f };
static constexpr float g_TWO_FIFTHS{ 0.4f };
static constexpr float g_THREE_FIFTHS{ 0.6f };
static constexpr float g_SEVEN_TENTHS{ 0.7f};
static constexpr float g_FOUR_FIFTHS{ 0.8f };
static constexpr float g_NINE_TENTHS{ 0.9f };

// Sprite ID's
const enum spriteIdInts
{
	nullpng = -1,
	fontMedpng,
	fontBigpng,
	fivepointpng,
	floorpng,
	healthpng,
	blockbreakpng,
	blockpng,
	platBluepng,
	platGreenpng,
	platPinkpng,
	platRedpng,
	platSpecialpng,
	platYellowpng,
	spikespng,
	ultimateTokenpng,
	tenpointpng,
	thirtypointpng,
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

// These enums are used to keep the Draw and update orders easy to access and alter
const enum updateOrder
{
	UPDATE_ORDER_PLAYER,
	UPDATE_ORDER_FLOOR,
	UPDATE_ORDER_LBARRIER,
	UPDATE_ORDER_CEILING,
	UPDATE_ORDER_RBARRIER,
	UPDATE_ORDER_PLATFORM,
	UPDATE_ORDER_PICKUP,
	UPDATE_ORDER_BLOCK,
	UPDATE_ORDER_SPIKE,
	UPDATE_ORDER_HEALTH,
	UPDATE_ORDER_ULTIMATE,
};

const enum drawOrder
{
	DRAW_ORDER_PLAYER,
	DRAW_ORDER_FLOOR,
	DRAW_ORDER_PLATFORM,
	DRAW_ORDER_PICKUP,
	DRAW_ORDER_BLOCK,
	DRAW_ORDER_SPIKE,
	DRAW_ORDER_HEALTH,
	DRAW_ORDER_ULTIMATE,
};

// Movement constants
static constexpr float g_GRAVITY{ (30.0f / 60.0f) }; // Acceleration due to GRAVITY
static constexpr float g_MOVE_ACC{ (45.0f / 60.0f) }; // Acceleration when moving
static constexpr float g_STUN_ACC{(90.0f / 60.0f)};
static constexpr int g_JUMP_SPEED{ 4 }; // The speed of Jumping upwards
// Maximum jump duration in seconds
static constexpr int g_JUMP_DURATION{ 30 };
static constexpr int g_I_FRAMES_DURATION{ 15 };
static constexpr int g_BLINK_DURATION{ 3 };

// Min and max speed constants
static constexpr float g_MAX_SPEED_RUN{ 3.5 }; // Maximum horizontal speed
static constexpr int g_MAX_SPEED_FALL{ 5 }; // Maximum vertical speed (can fall faster than he can run)
static constexpr float g_MINIMUM_SPEED_RUN{ 0.25f }; // A minimum speed, when this is reached the player stops and changes to idle

// The excess pixels on the zool sprites
static constexpr int g_PIXEL_EXCESS_X_ZOOL{ 10 };
static constexpr int g_PIXEL_EXCESS_Y_ZOOL{ 8 };

// Used in the resolution of horizontal collisions
// This is to prevent the player becoming stuck within an object
static constexpr int g_PIXEL_BUFFER{ 2 };

// Various animation speed's
static constexpr int g_RUN_ANIM_SPEED{32};
static constexpr int g_SINGLE_FRAME_ANIM_SPEED{ 1 };
static constexpr int g_TWO_FRAME_ANIM_SPEED{6};
static constexpr int g_BLOCK_BREAK_ANIM_SPEED{ 12 };
static constexpr int g_BLOCK_REAPPEAR{ 48 };

//Platform constants
static constexpr int g_PLATFORM_AMOUNT{ 15 };
static constexpr float g_HALF_SIZE_PLAT_X{ 24.0f };
static constexpr float g_HALF_SIZE_PLAT_Y{ 10.0f };

// The half-size of small object's in the game
// As multiple items are this size it was stored in a constant
static constexpr float g_HALF_SIZE_SMALL_OBJ{ 8.0f };

// Pickup constants
static constexpr int g_PICKUP_AMOUNT{ 40 };
static constexpr int g_FIVE_POINTS{ 5 };
static constexpr int g_TEN_POINTS{ 10 };
static constexpr int g_THIRTY_POINTS{ 30 };

// Positions for the ZOOL easter egg pickups, here for easier modification
// X positions
// Z 
static constexpr float g_Z_LEFT_X{ 640 + g_DISPLAY_WIDTH * g_QUARTER };
static constexpr float g_Z_MIDDLE_X{ 664 + g_DISPLAY_WIDTH * g_QUARTER };
static constexpr float g_Z_RIGHT_X{ 688 + g_DISPLAY_WIDTH * g_QUARTER };
static constexpr float g_Z_DIAGONAL_LEFT_X{ 656 + g_DISPLAY_WIDTH * g_QUARTER };
static constexpr float g_Z_DIAGONAL_RIGHT_X{ 672 + g_DISPLAY_WIDTH * g_QUARTER };

// O_FIRST
static constexpr float g_O_FIRST_LEFT_X{ 752 + g_DISPLAY_WIDTH * g_QUARTER };
static constexpr float g_O_FIRST_MIDDLE_X{ 776 + g_DISPLAY_WIDTH * g_QUARTER };
static constexpr float g_O_FIRST_RIGHT_X{ 800 + g_DISPLAY_WIDTH * g_QUARTER };

// O_SECOND 
static constexpr float g_O_SECOND_LEFT_X{ 880 + g_DISPLAY_WIDTH * g_QUARTER };
static constexpr float g_O_SECOND_MIDDLE_X{ 904 + g_DISPLAY_WIDTH * g_QUARTER };
static constexpr float g_O_SECOND_RIGHT_X{ 928 + g_DISPLAY_WIDTH * g_QUARTER };

// L 
static constexpr float g_L_LEFT_X{ 1008 + g_DISPLAY_WIDTH * g_QUARTER };
static constexpr float g_L_MIDDLE_X{ 1032 + g_DISPLAY_WIDTH * g_QUARTER };
static constexpr float g_L_RIGHT_X{ 1056 + g_DISPLAY_WIDTH * g_QUARTER };

// Y axis positions
// Letter height
static constexpr float g_LETTER_TOP_Y{ 366 - (g_DISPLAY_HEIGHT * g_THIRD + g_PIXELS_PER_UNIT_DOUBLE) };
static constexpr float g_LETTER_MIDDLE_TOP_Y{ 414 - (g_DISPLAY_HEIGHT * g_THIRD + g_PIXELS_PER_UNIT_DOUBLE) };
static constexpr float g_LETTER_MIDDLE_BOTTOM_Y{ 390 - (g_DISPLAY_HEIGHT * g_THIRD + g_PIXELS_PER_UNIT_DOUBLE) };
static constexpr float g_LETTER_BOTTOM_Y{ 438 - (g_DISPLAY_HEIGHT * g_THIRD + g_PIXELS_PER_UNIT_DOUBLE) };

// Block and spike constants
static constexpr int g_BLOCK_AMOUNT{ 16 };
static constexpr int g_SPIKE_AMOUNT{ 16 };

// Health pickup constants
static const int g_HEALTH_AMOUNT{ 2 };

// Player constants
static const Point2f g_INITIAL_PLAYER_POS = { static_cast<float>(g_DISPLAY_WIDTH * g_TWO_FIFTHS), static_cast<float>(g_LEVEL_HEIGHT - 2 * g_ZOOL_SIZE) } ;
static constexpr int g_MAX_HEALTH_PLAYER{ 6 };
static constexpr int g_MIN_HEALTH_PLAYER{ 1 };

// Camera struct: contains the position and size of the camera
struct Camera
{
	Point2f pos{ 0.0f, 0.0f };
	const float width{ g_DISPLAY_WIDTH };
	const float height{ g_DISPLAY_HEIGHT };
};

// Struct to represent the game state
struct GameState
{
	// The time elapsed in the game
	float time{ 0.0f };
	// Player's score
	int score{ 0 };
	// Player's health
	int health{ 0 };
	// Reference to the camera
	Camera camera;
};

// Struct's representing game object's that there are multiple of
// These objects are created in a data oriented manner
struct PlatformData
{
	Point2f pos{0.0f, 0.0f};
	Point2f HalfSizePlat{ g_HALF_SIZE_PLAT_X, g_HALF_SIZE_PLAT_Y };
	spriteIdInts colour{ nullpng };
};

struct PickUpData
{
	Point2f pos{ 0.0f, 0.0f };
	Point2f HalfSizePickUp{ g_HALF_SIZE_SMALL_OBJ, g_HALF_SIZE_SMALL_OBJ };
	spriteIdInts pickupSprite{ nullpng };
	int pointValue{ 0 };
};

struct BlockData
{
	Point2f pos{ 0.0f, 0.0f };
	Point2f HalfSizeBlock{ g_HALF_SIZE_SMALL_OBJ, g_HALF_SIZE_SMALL_OBJ };
	spriteIdInts blockSprite{ nullpng };
};

struct SpikeData
{
	Point2f pos{ 0.0f, 0.0f };
	Point2f HalfSizeSpike{ g_HALF_SIZE_SMALL_OBJ, g_HALF_SIZE_SMALL_OBJ };
};

struct HealthData
{
	Point2f pos{ 0.0f, 0.0f };
	Point2f HalfSizeHealth{ g_HALF_SIZE_SMALL_OBJ, g_HALF_SIZE_SMALL_OBJ };
};

enum class GameStatusState
{
	// Need to add title state
	TITLE_STATE = 0,
	PLAY_STATE,
	WIN_STATE,
	GAMEOVER_STATE
};

// GameStatus state variables and functions
static GameStatusState m_gameStatusState{ GameStatusState::TITLE_STATE };

inline void SetGameStatusState(GameStatusState gameStatusState) { m_gameStatusState = gameStatusState; }
inline GameStatusState GetGameStatusState() { return m_gameStatusState; }

static bool g_IS_LEVEL_CREATED{ false };

void TitleStateUpdate();
void PlayStateUpdate();
void GameOverStateUpdate();
void WinStateUpdate();

void Createg_LEVEL();
void PlaySpawnAll();
