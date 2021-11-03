#include "MainGame.h"
#include "LeftBarrier.h"
#include "Floor.h"
#include "Ceiling.h"
#include "RightBarrier.h"
#include "Player.h"
#include "Platform.h"
#include "Pickup.h"
#include "Block.h"
#include "Spike.h"
#define PLAY_IMPLEMENTATION
#include "Play.h"
#include <array>

GameState gameState;
PlatformData platData;
PickUpData pickUpData;
BlockData blockData;
SpikeData spikeData;

// The entry point for a Windows program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( S_DISPLAY_WIDTH, S_DISPLAY_HEIGHT, S_DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground( "Data\\Backgrounds\\Background.png" );

	// Spawn game world
	Floor::Spawn();
	LBarrier::Spawn(gameState);
	Ceiling::Spawn(gameState);
	RBarrier::Spawn(gameState);
	Player::Spawn();

	// Platform data as an array of structs
	std::array<PlatformData, PLATFORM_AMOUNT>platformArray
	{{
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH / 2), (LEVEL_HEIGHT * NINE_TENTHS - HALF_SIZE_SMALL_OBJ)}),
			platData.HalfSizePlat,
			(platData.colour = platPinkpng)
		},
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH * QUARTER), (LEVEL_HEIGHT * FOUR_FIFTHS)}),
			platData.HalfSizePlat,
			(platData.colour = platBluepng)
		}, 
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH / 2), (LEVEL_HEIGHT * SEVEN_TENTHS)}),
			platData.HalfSizePlat,
			(platData.colour = platYellowpng)
		},
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH * QUARTER) , (LEVEL_HEIGHT * THREE_FIFTHS)}),
			platData.HalfSizePlat,
			(platData.colour = platRedpng)
		},
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH / 2), (LEVEL_HEIGHT / 2)}),
			platData.HalfSizePlat,
			(platData.colour = platGreenpng)
		},
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH * THREE_QUARTERS), (LEVEL_HEIGHT / 2)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
	}};
	
	for (PlatformData platData : platformArray)
	{
		Platform::Spawn(platData);
	}

	std::array<PickUpData, PICKUP_AMOUNT>pickUpArray
	{ {
		PickUpData
		{
			(pickUpData.pos = {S_DISPLAY_WIDTH * FOUR_FIFTHS, LEVEL_HEIGHT - ( 2 * ZOOL_SIZE - S_PIXELS_PER_UNIT)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = fivepointpng),
			(pickUpData.pointValue = FIVE_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(S_DISPLAY_WIDTH * THREE_QUARTERS), ((LEVEL_HEIGHT / 2) - (ZOOL_SIZE - S_PIXELS_PER_UNIT))}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = fivepointpng),
			(pickUpData.pointValue = FIVE_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(S_DISPLAY_WIDTH), ((LEVEL_HEIGHT / 2) - (ZOOL_SIZE - HALF_SIZE_SMALL_OBJ))}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = tenpointpng),
			(pickUpData.pointValue = TEN_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(S_DISPLAY_WIDTH / 2), ((LEVEL_HEIGHT / 2) - (ZOOL_SIZE - S_PIXELS_PER_UNIT))}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = fivepointpng),
			(pickUpData.pointValue = FIVE_POINTS)
		}
	} };

	for (PickUpData pickUpData : pickUpArray)
	{
		Pickup::Spawn(pickUpData);
	}

	std::array<BlockData, BLOCK_AMOUNT>blockArray
	{ {
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		}
	} };

	for (BlockData blockData : blockArray)
	{
		Block::Spawn(blockData);
	}

	std::array<SpikeData, SPIKE_AMOUNT>spikeArray
	{ {
		SpikeData
		{
			(spikeData.pos = {(S_DISPLAY_WIDTH), ((LEVEL_HEIGHT) - (2 * (ZOOL_SIZE) - (S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		}
	} };

	for (SpikeData spikeData : spikeArray)
	{
		Spike::Spawn(spikeData);
	}
}

// Called by the PlayBuffer once for each frame of the game (60 times a second!)
bool MainGameUpdate(float elapsedTime)
{
	// Keeping track of the elapsed time 
	gameState.time += elapsedTime;
	Play::DrawBackground();

	GameObject::DrawAll(gameState);

	Play::DrawFontText("font24px", "SCORE: " + std::to_string(gameState.score),
		{ S_DISPLAY_WIDTH * FIFTH,  S_DISPLAY_HEIGHT * TENTH }, Play::CENTRE);

	std::vector <GameObject*> oList = GameObject::GetTypeList(GameObject::Type::OBJ_ALL);
	for (GameObject* gameObject : oList)
	{
		if (gameObject->GetType() == GameObject::Type::OBJ_PLAYER)
		{
			Player* player = static_cast<Player*>(gameObject);
			gameState.health = player->GetHealth();
		}
	}

	Play::DrawFontText("font24px", "HEALTH: " + std::to_string(gameState.health),
		{ S_DISPLAY_WIDTH * FOUR_FIFTHS,  S_DISPLAY_HEIGHT * TENTH }, Play::CENTRE);

	Play::PresentDrawingBuffer();

	GameObject::UpdateAll(gameState);

	// Allows the player to easily exit the game
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	std::vector <GameObject*> oList = GameObject::GetTypeList(GameObject::Type::OBJ_ALL);
	for (GameObject* o : oList)
	{
		o->SetActive(false);
	}
	Play::DestroyManager();
	GameObject::DestroyAll();
	return PLAY_OK;
}

