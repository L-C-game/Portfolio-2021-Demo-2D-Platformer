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
}

// Called by the PlayBuffer once for each frame of the game (60 times a second!)
bool MainGameUpdate(float elapsedTime)
{
	// Keeping track of the elapsed time 
	gameState.time += elapsedTime;
	Play::CentreAllSpriteOrigins();
	Play::DrawBackground();

	GameObject::DrawAll(gameState);

	switch (GetGameStatusState())
	{
	case GameStatusState::TITLE_STATE:
		TitleStateUpdate(gameState);
		break;
	case GameStatusState::PLAY_STATE:
		PlayStateUpdate(gameState);
		GameObject::UpdateAll(gameState);
		break;
	case GameStatusState::GAMEOVER_STATE:
		GameOverStateUpdate(gameState);
		break;
	}

	Play::PresentDrawingBuffer();
	// Allows the player to easily exit the game
	return Play::KeyDown(VK_ESCAPE);
}

void TitleStateUpdate(GameState& gameState)
{
	// Reset the score
	gameState.score = 0;
	PlaySpawnAll(gameState);

	if (Play::KeyPressed(VK_RETURN))
	{
		SetGameStatusState(GameStatusState::PLAY_STATE);
	}

	Play::DrawFontText("font36px", "ZOOL IN DEMOLAND",
		{ S_DISPLAY_WIDTH / 2,  S_DISPLAY_HEIGHT * TENTH }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS RETURN/ENTER TO PLAY!",
		{ S_DISPLAY_WIDTH / 2 ,  S_DISPLAY_HEIGHT * TWO_FIFTHS }, Play::CENTRE);

	Play::DrawFontText("font24px", "USE THE DIRECTIONAL BUTTONS TO MOVE,",
		{ S_DISPLAY_WIDTH / 2,  S_DISPLAY_HEIGHT / 2 }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS SPACEBAR TO JUMP,",
		{ S_DISPLAY_WIDTH / 2,  S_DISPLAY_HEIGHT * THREE_FIFTHS }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS ESCAPE TO QUIT.",
		{ S_DISPLAY_WIDTH / 2,  S_DISPLAY_HEIGHT * SEVEN_TENTHS }, Play::CENTRE);
}

void PlayStateUpdate(GameState& gameState)
{
	Play::DrawFontText("font24px", "SCORE: " + std::to_string(gameState.score),
		{ S_DISPLAY_WIDTH * FIFTH,  S_DISPLAY_HEIGHT * TENTH }, Play::CENTRE);

	std::vector <GameObject*> oList = GameObject::GetTypeList(GameObject::Type::OBJ_ALL);
	for (GameObject* gameObject : oList)
	{
		if (gameObject->GetType() == GameObject::Type::OBJ_PLAYER)
		{
			Player* player = static_cast<Player*>(gameObject);
			gameState.health = player->GetHealth();
			gameState.score = player->GetScore();
		}
	}

	Play::DrawFontText("font24px", "HEALTH: " + std::to_string(gameState.health),
		{ S_DISPLAY_WIDTH * FOUR_FIFTHS,  S_DISPLAY_HEIGHT * TENTH }, Play::CENTRE);

	if (gameState.health == 0)
	{
		SetGameStatusState(GameStatusState::GAMEOVER_STATE);
	}
}

void GameOverStateUpdate(GameState& gameState)
{

	if (Play::KeyPressed(VK_RETURN))
	{
		SetGameStatusState(GameStatusState::TITLE_STATE);
	}

	std::vector <GameObject*> oList = GameObject::GetTypeList(GameObject::Type::OBJ_ALL);
	for (GameObject* gameObject : oList)
	{
		if (gameObject->GetType() == GameObject::Type::OBJ_PLAYER)
		{
			Player* player = static_cast<Player*>(gameObject);
			player->ResetPlayer();
		}
	}

	Play::DrawFontText("font36px", "GAME OVER",
		{ S_DISPLAY_WIDTH / 2,  S_DISPLAY_HEIGHT * TENTH }, Play::CENTRE);

	Play::DrawFontText("font24px", "FINAL SCORE: " + std::to_string(gameState.score),
		{ S_DISPLAY_WIDTH / 2 ,  S_DISPLAY_HEIGHT * TWO_FIFTHS }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS RETURN/ENTER TO RETRY!",
		{ S_DISPLAY_WIDTH / 2,  S_DISPLAY_HEIGHT / 2}, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS ESCAPE TO QUIT.",
		{ S_DISPLAY_WIDTH / 2,  S_DISPLAY_HEIGHT * THREE_FIFTHS }, Play::CENTRE);
}

void PlaySpawnAll(GameState& gameState)
{
	// Spawn game world
	Floor::Spawn();
	Player::Spawn();

	// Platform data as an array of structs
	std::array<PlatformData, PLATFORM_AMOUNT>platformArray
	{ {
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
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH * 2), (LEVEL_HEIGHT / 2)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH * THREE_QUARTERS - (S_DISPLAY_WIDTH * QUARTER) / 2), S_DISPLAY_HEIGHT + (S_DISPLAY_HEIGHT * THREE_QUARTERS * THIRD)}),
			platData.HalfSizePlat,
			(platData.colour = platPinkpng)
		},
		PlatformData
		{
			(platData.pos = {((S_DISPLAY_WIDTH / 2) - (S_DISPLAY_WIDTH * QUARTER) / 2), (S_DISPLAY_HEIGHT + (S_DISPLAY_HEIGHT * QUARTER) / 2)}),
			platData.HalfSizePlat,
			(platData.colour = platBluepng)
		}
	} };

	for (PlatformData platData : platformArray)
	{
		Platform::Spawn(platData);
	}

	std::array<PickUpData, PICKUP_AMOUNT>pickUpArray
	{ {
		PickUpData
		{
			(pickUpData.pos = {S_DISPLAY_WIDTH * FOUR_FIFTHS, LEVEL_HEIGHT - (2 * ZOOL_SIZE - S_PIXELS_PER_UNIT)}),
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
			(pickUpData.pos = {(S_DISPLAY_WIDTH + HALF_SIZE_SMALL_OBJ), ((LEVEL_HEIGHT / 2) - (ZOOL_SIZE - HALF_SIZE_SMALL_OBJ))}),
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
		},
		PickUpData
		{
			(pickUpData.pos = {(S_DISPLAY_WIDTH * QUARTER + S_DISPLAY_WIDTH + HALF_SIZE_SMALL_OBJ), ((LEVEL_HEIGHT / 2) - (ZOOL_SIZE - HALF_SIZE_SMALL_OBJ))}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = fivepointpng),
			(pickUpData.pointValue = FIVE_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(S_DISPLAY_WIDTH + (S_DISPLAY_WIDTH / 2) + HALF_SIZE_SMALL_OBJ), ((LEVEL_HEIGHT / 2) - (ZOOL_SIZE - HALF_SIZE_SMALL_OBJ))}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = fivepointpng),
			(pickUpData.pointValue = FIVE_POINTS)
		},
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
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH * QUARTER + S_DISPLAY_WIDTH), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH * QUARTER + S_DISPLAY_WIDTH + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH / 2 + S_DISPLAY_WIDTH), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH / 2 + S_DISPLAY_WIDTH + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH * THREE_QUARTERS + S_DISPLAY_WIDTH), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH * THREE_QUARTERS + S_DISPLAY_WIDTH + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
	} };

	for (BlockData blockData : blockArray)
	{
		Block::Spawn(blockData);
	}

	std::array<SpikeData, SPIKE_AMOUNT>spikeArray
	{ {
		SpikeData
		{
			(spikeData.pos = {(S_DISPLAY_WIDTH), ((LEVEL_HEIGHT) - (2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(S_DISPLAY_WIDTH + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT)-(2 * (ZOOL_SIZE) - (S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(S_DISPLAY_WIDTH + S_DISPLAY_WIDTH * QUARTER), ((LEVEL_HEIGHT)-(2 * (ZOOL_SIZE) - (S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(S_DISPLAY_WIDTH + (S_DISPLAY_WIDTH * QUARTER) + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT) - (2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(S_DISPLAY_WIDTH + (S_DISPLAY_WIDTH / 2)), ((LEVEL_HEIGHT)-(2 * (ZOOL_SIZE) - (S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(S_DISPLAY_WIDTH + (S_DISPLAY_WIDTH / 2) + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT) - (2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(S_DISPLAY_WIDTH + (S_DISPLAY_WIDTH * THREE_QUARTERS)), ((LEVEL_HEIGHT) - (2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(S_DISPLAY_WIDTH + (S_DISPLAY_WIDTH * THREE_QUARTERS) + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT) - (2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
	} };

	for (SpikeData spikeData : spikeArray)
	{
		Spike::Spawn(spikeData);
	}

	LBarrier::Spawn(gameState);
	Ceiling::Spawn(gameState);
	RBarrier::Spawn(gameState);
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

