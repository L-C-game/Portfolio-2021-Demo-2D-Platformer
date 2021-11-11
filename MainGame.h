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
constexpr float THIRD{ 0.333333333333f };
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
constexpr int MAX_SPEED_FALL{ 5 }; // Maximum vertical speed (can fall faster than he can run)
constexpr float MINIMUM_SPEED_RUN{ 0.25f }; // A minimum speed, when this is reached the player stops and changes to idle

// The excess pixels on the zool sprites
constexpr int PIXEL_EXCESS_X_ZOOL{ 10 };
constexpr int PIXEL_EXCESS_Y_ZOOL{ 8 };

// Used in the resolution of horizontal collisions
// This is to prevent the player becoming stuck within an object
constexpr int PIXEL_BUFFER{ 2 };

// Various animation speed's
constexpr int RUN_ANIM_SPEED{32};
constexpr int SINGLE_FRAME_ANIM_SPEED{ 1 };
constexpr int TWO_FRAME_ANIM_SPEED{6};
constexpr int BLOCK_BREAK_ANIM_SPEED{ 12 };
constexpr int BLOCK_REAPPEAR{ 48 };

//Platform constants
constexpr int PLATFORM_AMOUNT{ 15 };
constexpr float HALF_SIZE_PLAT_X{ 24.0f };
constexpr float HALF_SIZE_PLAT_Y{ 10.0f };

// The half-size of small object's in the game
// As multiple items are this size it was stored in a constant
constexpr float HALF_SIZE_SMALL_OBJ{ 8.0f };

// Pickup constants
constexpr int PICKUP_AMOUNT{ 40 };
constexpr int FIVE_POINTS{ 5 };
constexpr int TEN_POINTS{ 10 };
constexpr int THIRTY_POINTS{ 30 };

// Positions for the ZOOL easter egg pickups, here for easier modification
// X positions
// Z 
constexpr float Z_LEFT_X{ 640 + S_DISPLAY_WIDTH * QUARTER };
constexpr float Z_MIDDLE_X{ 664 + S_DISPLAY_WIDTH * QUARTER };
constexpr float Z_RIGHT_X{ 688 + S_DISPLAY_WIDTH * QUARTER };
constexpr float Z_DIAGONAL_LEFT_X{ 656 + S_DISPLAY_WIDTH * QUARTER };
constexpr float Z_DIAGONAL_RIGHT_X{ 672 + S_DISPLAY_WIDTH * QUARTER };

// O_FIRST
constexpr float O_FIRST_LEFT_X{ 752 + S_DISPLAY_WIDTH * QUARTER };
constexpr float O_FIRST_MIDDLE_X{ 776 + S_DISPLAY_WIDTH * QUARTER };
constexpr float O_FIRST_RIGHT_X{ 800 + S_DISPLAY_WIDTH * QUARTER };

// O_SECOND 
constexpr float O_SECOND_LEFT_X{ 880 + S_DISPLAY_WIDTH * QUARTER };
constexpr float O_SECOND_MIDDLE_X{ 904 + S_DISPLAY_WIDTH * QUARTER };
constexpr float O_SECOND_RIGHT_X{ 928 + S_DISPLAY_WIDTH * QUARTER };

// L 
constexpr float L_LEFT_X{ 1008 + S_DISPLAY_WIDTH * QUARTER };
constexpr float L_MIDDLE_X{ 1032 + S_DISPLAY_WIDTH * QUARTER };
constexpr float L_RIGHT_X{ 1056 + S_DISPLAY_WIDTH * QUARTER };

// Y positions
// Letter height
constexpr float LETTER_TOP_Y{ 366 - (S_DISPLAY_HEIGHT * THIRD + S_PIXELS_PER_UNIT_DOUBLE) }; 
constexpr float LETTER_MIDDLE_TOP_Y{ 414 - (S_DISPLAY_HEIGHT * THIRD + S_PIXELS_PER_UNIT_DOUBLE) };
constexpr float LETTER_MIDDLE_BOTTOM_Y{ 390 - (S_DISPLAY_HEIGHT * THIRD + S_PIXELS_PER_UNIT_DOUBLE) };
constexpr float LETTER_BOTTOM_Y{ 438 - (S_DISPLAY_HEIGHT * THIRD + S_PIXELS_PER_UNIT_DOUBLE) };

// Block and spike constants
constexpr int BLOCK_AMOUNT{ 16 };
constexpr int SPIKE_AMOUNT{ 16 };

// Health pickup constants
const int HEALTH_AMOUNT{ 2 };

// Player constants
const Point2f initialPlayerPos = { static_cast<float>(S_DISPLAY_WIDTH * TWO_FIFTHS), static_cast<float>(LEVEL_HEIGHT - 2 * ZOOL_SIZE) } ;
constexpr int MAX_HEALTH_PLAYER{ 6 };
constexpr int MIN_HEALTH_PLAYER{ 1 };

// Camera struct: contains the position and size of the camera
struct Camera
{
	Point2f pos{ 0.0f, 0.0f };
	const float width{ S_DISPLAY_WIDTH };
	const float height{ S_DISPLAY_HEIGHT };
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
	Point2f HalfSizePlat{ HALF_SIZE_PLAT_X, HALF_SIZE_PLAT_Y };
	spriteIdInts colour{ nullpng };
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

struct HealthData
{
	Point2f pos{ 0.0f, 0.0f };
	Point2f HalfSizeHealth{ HALF_SIZE_SMALL_OBJ, HALF_SIZE_SMALL_OBJ };
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
static GameStatusState GetGameStatusState() { return m_gameStatusState; }

static bool isLevelCreated{ false };

void TitleStateUpdate();
void PlayStateUpdate();
void GameOverStateUpdate();
void WinStateUpdate();

void CreateLevel();
void PlaySpawnAll();
