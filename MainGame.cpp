/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

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
#include "Health.h"
#include "UltimateToken.h"
#define PLAY_IMPLEMENTATION
#include "Play.h"
#include <array>

GameState gameState;
PlatformData platData;
PickUpData pickUpData;
BlockData blockData;
SpikeData spikeData;
HealthData healthData;

// The entry point for a Windows program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( g_DISPLAY_WIDTH, g_DISPLAY_HEIGHT, g_DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground( "Data\\Backgrounds\\Background.png" );

	Play::StartAudioLoop("untitled");
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
		TitleStateUpdate();
		break;
	case GameStatusState::PLAY_STATE:
		PlayStateUpdate();
		GameObject::UpdateAll(gameState);
		break;
	case GameStatusState::GAMEOVER_STATE:
		GameOverStateUpdate();
		break;
	case GameStatusState::WIN_STATE:
		WinStateUpdate();
		break;
	}

	Play::PresentDrawingBuffer();
	// Allows the player to easily exit the game
	return Play::KeyDown(VK_ESCAPE);
}

void TitleStateUpdate()
{
	// Reset the score
	gameState.score = 0;
	Createg_LEVEL();

	if (Play::KeyPressed(VK_RETURN))
	{
		SetGameStatusState(GameStatusState::PLAY_STATE);
	}

	Play::DrawFontText("font36px", "ZOOL IN DEMOLAND",
		{ g_DISPLAY_WIDTH / 2,  g_DISPLAY_HEIGHT * g_TENTH }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS RETURN/ENTER TO PLAY!",
		{ g_DISPLAY_WIDTH / 2 ,  g_DISPLAY_HEIGHT * g_TWO_FIFTHS }, Play::CENTRE);

	Play::DrawFontText("font24px", "USE THE DIRECTIONAL BUTTONS TO MOVE,",
		{ g_DISPLAY_WIDTH / 2,  g_DISPLAY_HEIGHT / 2 }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS SPACEBAR TO JUMP,",
		{ g_DISPLAY_WIDTH / 2,  g_DISPLAY_HEIGHT * g_THREE_FIFTHS }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS ESCAPE TO QUIT.",
		{ g_DISPLAY_WIDTH / 2,  g_DISPLAY_HEIGHT * g_SEVEN_TENTHS }, Play::CENTRE);
}

void PlayStateUpdate()
{
	Play::DrawFontText("font24px", "SCORE: " + std::to_string(gameState.score),
		{ g_DISPLAY_WIDTH * g_FIFTH,  g_DISPLAY_HEIGHT * g_TENTH }, Play::CENTRE);

	std::vector <GameObject*> oList = GameObject::GetTypeList(GameObject::Type::OBJ_ALL);
	for (GameObject* gameObject : oList)
	{
		if (gameObject->GetType() == GameObject::Type::OBJ_PLAYER)
		{
			Player* player = static_cast<Player*>(gameObject);
			gameState.health = player->GetHealth();
			gameState.score = player->GetScore();

			if (player->GetHasUltimate())
			{
				Play::StopAudioLoop("untitled");
				Play::StartAudioLoop("HET");
				SetGameStatusState(GameStatusState::WIN_STATE);
			}
		}
	}

	Play::DrawFontText("font24px", "HEALTH: " + std::to_string(gameState.health),
		{ g_DISPLAY_WIDTH * g_FOUR_FIFTHS,  g_DISPLAY_HEIGHT * g_TENTH }, Play::CENTRE);

	if (gameState.health == 0)
	{
		Play::StopAudioLoop("untitled");
		Play::StartAudioLoop("weirdWavvyThing");
		SetGameStatusState(GameStatusState::GAMEOVER_STATE);
	}
}

void GameOverStateUpdate()
{

	if (Play::KeyPressed(VK_RETURN))
	{
		Play::StopAudioLoop("weirdWavvyThing");
		Play::StartAudioLoop("untitled");
		g_IS_LEVEL_CREATED = false;
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
		{ g_DISPLAY_WIDTH / 2,  g_DISPLAY_HEIGHT * g_TENTH }, Play::CENTRE);

	Play::DrawFontText("font24px", "FINAL SCORE: " + std::to_string(gameState.score),
		{ g_DISPLAY_WIDTH / 2 ,  g_DISPLAY_HEIGHT * g_TWO_FIFTHS }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS RETURN/ENTER TO RETRY!",
		{ g_DISPLAY_WIDTH / 2,  g_DISPLAY_HEIGHT / 2}, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS ESCAPE TO QUIT.",
		{ g_DISPLAY_WIDTH / 2,  g_DISPLAY_HEIGHT * g_THREE_FIFTHS }, Play::CENTRE);
}

void WinStateUpdate()
{

	if (Play::KeyPressed(VK_RETURN))
	{
		Play::StopAudioLoop("HET");
		Play::StartAudioLoop("untitled");
		g_IS_LEVEL_CREATED = false;
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

	Play::DrawFontText("font36px", "YOU WIN!",
		{ g_DISPLAY_WIDTH / 2,  g_DISPLAY_HEIGHT * g_TENTH }, Play::CENTRE);

	Play::DrawFontText("font24px", "FINAL SCORE: " + std::to_string(gameState.score),
		{ g_DISPLAY_WIDTH / 2 ,  g_DISPLAY_HEIGHT * g_TWO_FIFTHS }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS RETURN/ENTER TO RETRY!",
		{ g_DISPLAY_WIDTH / 2,  g_DISPLAY_HEIGHT / 2 }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS ESCAPE TO QUIT.",
		{ g_DISPLAY_WIDTH / 2,  g_DISPLAY_HEIGHT * g_THREE_FIFTHS }, Play::CENTRE);
}

void Createg_LEVEL()
{
	if (!g_IS_LEVEL_CREATED)
	{
		PlaySpawnAll();
	}
	g_IS_LEVEL_CREATED = true;
}

// Setting up the Game world in a data oriented way
void PlaySpawnAll()
{
	Floor::Spawn();
	Player::Spawn();
	UltimateToken::Spawn();

	// Platform data as an array of structs
	std::array<PlatformData, g_PLATFORM_AMOUNT>platformArray
	{ {
		PlatformData
		{
			(platData.pos = {(g_DISPLAY_WIDTH / 2), (g_LEVEL_HEIGHT * g_NINE_TENTHS - g_HALF_SIZE_SMALL_OBJ)}),
			platData.HalfSizePlat,
			(platData.colour = platPinkpng)
		},
		PlatformData
		{
			(platData.pos = {(g_DISPLAY_WIDTH * g_QUARTER), (g_LEVEL_HEIGHT * g_FOUR_FIFTHS)}),
			platData.HalfSizePlat,
			(platData.colour = platBluepng)
		},
		PlatformData
		{
			(platData.pos = {(g_DISPLAY_WIDTH / 2), (g_LEVEL_HEIGHT * g_SEVEN_TENTHS)}),
			platData.HalfSizePlat,
			(platData.colour = platYellowpng)
		},
		PlatformData
		{
			(platData.pos = {(g_DISPLAY_WIDTH * g_QUARTER) , (g_LEVEL_HEIGHT * g_THREE_FIFTHS)}),
			platData.HalfSizePlat,
			(platData.colour = platRedpng)
		},
		PlatformData
		{
			(platData.pos = {(g_DISPLAY_WIDTH / 2), (g_LEVEL_HEIGHT / 2)}),
			platData.HalfSizePlat,
			(platData.colour = platGreenpng)
		},
		PlatformData
		{
			(platData.pos = {(g_DISPLAY_WIDTH * g_THREE_QUARTERS), (g_LEVEL_HEIGHT / 2)}),
			platData.HalfSizePlat,
			(platData.colour = platYellowpng)
		},
		PlatformData
		{
			(platData.pos = {(g_DISPLAY_WIDTH * 2), (g_LEVEL_HEIGHT / 2)}),
			platData.HalfSizePlat,
			(platData.colour = platYellowpng)
		},
		PlatformData
		{
			(platData.pos = {((g_DISPLAY_WIDTH / 2) - (g_DISPLAY_WIDTH * g_QUARTER)), (g_DISPLAY_HEIGHT + (g_DISPLAY_HEIGHT * g_QUARTER))}),
			platData.HalfSizePlat,
			(platData.colour = platPinkpng)
		},
		PlatformData
		{
			(platData.pos = {(g_DISPLAY_WIDTH / 2), (g_DISPLAY_HEIGHT)}),
			platData.HalfSizePlat,
			(platData.colour = platBluepng)
		},
		PlatformData
		{
			(platData.pos = {(g_DISPLAY_WIDTH/ 2 + g_DISPLAY_WIDTH * g_QUARTER), (g_DISPLAY_HEIGHT)}),
			platData.HalfSizePlat,
			(platData.colour = platRedpng)
		},
		PlatformData
		{
			(platData.pos = {(g_DISPLAY_WIDTH), (g_DISPLAY_HEIGHT - g_PIXELS_PER_UNIT_DOUBLE)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
		PlatformData
		{
			(platData.pos = {((g_DISPLAY_WIDTH) + (g_DISPLAY_WIDTH * g_QUARTER)), (g_DISPLAY_HEIGHT - g_PIXELS_PER_UNIT_DOUBLE)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
		PlatformData
		{
			(platData.pos = {((g_DISPLAY_WIDTH) + (g_DISPLAY_WIDTH / 2)), (g_DISPLAY_HEIGHT - g_PIXELS_PER_UNIT_DOUBLE)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
		PlatformData
		{
			(platData.pos = {((g_DISPLAY_WIDTH) + (g_DISPLAY_WIDTH * g_THREE_QUARTERS)), (g_DISPLAY_HEIGHT - g_PIXELS_PER_UNIT_DOUBLE)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
		PlatformData
		{
			(platData.pos = {(g_DISPLAY_WIDTH * 2), (g_DISPLAY_HEIGHT - g_PIXELS_PER_UNIT_DOUBLE)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
	} };

	for (PlatformData platformsData : platformArray)
	{
		Platform::Spawn(platformsData);
	}

	std::array<PickUpData, g_PICKUP_AMOUNT>pickUpArray
	{ {
		PickUpData
		{
			(pickUpData.pos = {g_DISPLAY_WIDTH * g_FOUR_FIFTHS, g_LEVEL_HEIGHT - (2 * g_ZOOL_SIZE - g_PIXELS_PER_UNIT)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = fivepointpng),
			(pickUpData.pointValue = g_FIVE_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_DISPLAY_WIDTH * g_THREE_QUARTERS), ((g_LEVEL_HEIGHT / 2) - (g_ZOOL_SIZE - g_PIXELS_PER_UNIT))}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = fivepointpng),
			(pickUpData.pointValue = g_FIVE_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_DISPLAY_WIDTH + g_HALF_SIZE_SMALL_OBJ), ((g_LEVEL_HEIGHT / 2) - (g_ZOOL_SIZE - g_HALF_SIZE_SMALL_OBJ))}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = tenpointpng),
			(pickUpData.pointValue = g_TEN_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_DISPLAY_WIDTH / 2), ((g_LEVEL_HEIGHT / 2) - (g_ZOOL_SIZE - g_PIXELS_PER_UNIT))}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = fivepointpng),
			(pickUpData.pointValue = g_FIVE_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_DISPLAY_WIDTH * g_QUARTER + g_DISPLAY_WIDTH + g_HALF_SIZE_SMALL_OBJ), ((g_LEVEL_HEIGHT / 2) - (g_ZOOL_SIZE - g_HALF_SIZE_SMALL_OBJ))}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = fivepointpng),
			(pickUpData.pointValue = g_FIVE_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_DISPLAY_WIDTH + (g_DISPLAY_WIDTH / 2) + g_HALF_SIZE_SMALL_OBJ), ((g_LEVEL_HEIGHT / 2) - (g_ZOOL_SIZE - g_HALF_SIZE_SMALL_OBJ))}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = fivepointpng),
			(pickUpData.pointValue = g_FIVE_POINTS)
		},


		// Easter egg for Zool's 30year anniversary next year
		// START OF Z
		PickUpData
		{
			(pickUpData.pos = {g_Z_LEFT_X, (g_LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {g_Z_MIDDLE_X, (g_LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {g_Z_RIGHT_X, (g_LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},

		PickUpData
		{
			(pickUpData.pos = {g_Z_DIAGONAL_LEFT_X, (g_LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {g_Z_DIAGONAL_RIGHT_X, (g_LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},

		PickUpData
		{
			(pickUpData.pos = {g_Z_LEFT_X, (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_Z_MIDDLE_X), (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_Z_RIGHT_X), (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		// END OF Z
		// START OF O 
		PickUpData 
		{
			(pickUpData.pos = {(g_O_FIRST_LEFT_X), (g_LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_O_FIRST_MIDDLE_X), (g_LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_O_FIRST_RIGHT_X), (g_LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},

		PickUpData 
		{
			(pickUpData.pos = {(g_O_FIRST_LEFT_X), (g_LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(g_O_FIRST_LEFT_X), (g_LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},

		PickUpData 
		{
			(pickUpData.pos = {(g_O_FIRST_RIGHT_X), (g_LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(g_O_FIRST_RIGHT_X), (g_LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},

		PickUpData 
		{
			(pickUpData.pos = {(g_O_FIRST_LEFT_X), (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_O_FIRST_MIDDLE_X), (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_O_FIRST_RIGHT_X), (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		// END OF O
		// START OF O 
		PickUpData 
		{
			(pickUpData.pos = {(g_O_SECOND_LEFT_X), (g_LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_O_SECOND_MIDDLE_X), (g_LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_O_SECOND_RIGHT_X), (g_LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},

		PickUpData 
		{
			(pickUpData.pos = {(g_O_SECOND_LEFT_X), (g_LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(g_O_SECOND_LEFT_X), (g_LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(g_O_SECOND_RIGHT_X), (g_LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(g_O_SECOND_RIGHT_X), (g_LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(g_O_SECOND_LEFT_X), (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_O_SECOND_MIDDLE_X), (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_O_SECOND_RIGHT_X), (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		// END OF O
		// START OF L
		PickUpData 
		{
			(pickUpData.pos = {(g_L_LEFT_X), (g_LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(g_L_LEFT_X), (g_LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(g_L_LEFT_X), (g_LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(g_L_LEFT_X), (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_L_MIDDLE_X), (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(g_L_RIGHT_X), (g_LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = g_THIRTY_POINTS)
		},
		// END OF L
	} };

	for (PickUpData pickUpsData : pickUpArray)
	{
		Pickup::Spawn(pickUpsData);
	}

	std::array<BlockData, g_BLOCK_AMOUNT>blockArray
	{ {
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH * g_QUARTER + g_DISPLAY_WIDTH), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH * g_QUARTER + g_DISPLAY_WIDTH + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH / 2 + g_DISPLAY_WIDTH), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH / 2 + g_DISPLAY_WIDTH + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH * g_THREE_QUARTERS + g_DISPLAY_WIDTH), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH * g_THREE_QUARTERS + g_DISPLAY_WIDTH + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},

		// Second section of falling blocks
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH * g_QUARTER + 2 * g_DISPLAY_WIDTH), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (2 * g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH * g_QUARTER + 2 * g_DISPLAY_WIDTH + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (2 * g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH / 2 + 2 * g_DISPLAY_WIDTH), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH / 2 + 2 * g_DISPLAY_WIDTH + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH * g_THREE_QUARTERS + 2 * g_DISPLAY_WIDTH), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - ( 2 * g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH * g_THREE_QUARTERS + 2 * g_DISPLAY_WIDTH + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (2 * g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH), ((g_LEVEL_HEIGHT * g_THREE_QUARTERS + (g_PIXELS_PER_UNIT_DOUBLE)) + (2 * g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(g_DISPLAY_WIDTH + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT * g_THREE_QUARTERS + (g_PIXELS_PER_UNIT_DOUBLE)) + (2 * g_ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
	} };

	for (BlockData blocksData : blockArray)
	{
		Block::Spawn(blocksData);
	}

	std::array<SpikeData, g_SPIKE_AMOUNT>spikeArray
	{ {
		SpikeData
		{
			(spikeData.pos = {(g_DISPLAY_WIDTH), ((g_LEVEL_HEIGHT) - (2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(g_DISPLAY_WIDTH + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT)-(2 * (g_ZOOL_SIZE) - (g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(g_DISPLAY_WIDTH + g_DISPLAY_WIDTH * g_QUARTER), ((g_LEVEL_HEIGHT)-(2 * (g_ZOOL_SIZE) - (g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(g_DISPLAY_WIDTH + (g_DISPLAY_WIDTH * g_QUARTER) + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT) - (2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(g_DISPLAY_WIDTH + (g_DISPLAY_WIDTH / 2)), ((g_LEVEL_HEIGHT)-(2 * (g_ZOOL_SIZE) - (g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(g_DISPLAY_WIDTH + (g_DISPLAY_WIDTH / 2) + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT) - (2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(g_DISPLAY_WIDTH + (g_DISPLAY_WIDTH * g_THREE_QUARTERS)), ((g_LEVEL_HEIGHT) - (2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(g_DISPLAY_WIDTH + (g_DISPLAY_WIDTH * g_THREE_QUARTERS) + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT) - (2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},

		// Second set of spikes
		SpikeData
		{
			(spikeData.pos = {(2 * g_DISPLAY_WIDTH), ((g_LEVEL_HEIGHT)-(2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * g_DISPLAY_WIDTH + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT)-(2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * g_DISPLAY_WIDTH + g_DISPLAY_WIDTH * g_QUARTER), ((g_LEVEL_HEIGHT)-(2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * g_DISPLAY_WIDTH + (g_DISPLAY_WIDTH * g_QUARTER) + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT)-(2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * g_DISPLAY_WIDTH + (g_DISPLAY_WIDTH / 2)), ((g_LEVEL_HEIGHT)-(2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * g_DISPLAY_WIDTH + (g_DISPLAY_WIDTH / 2) + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT)-(2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * g_DISPLAY_WIDTH + (g_DISPLAY_WIDTH * g_THREE_QUARTERS)), ((g_LEVEL_HEIGHT)-(2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * g_DISPLAY_WIDTH + (g_DISPLAY_WIDTH * g_THREE_QUARTERS) + g_PIXELS_PER_UNIT), ((g_LEVEL_HEIGHT)-(2 * (g_ZOOL_SIZE)-(g_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
	} };

	for (SpikeData spikesData : spikeArray)
	{
		Spike::Spawn(spikesData);
	}

	std::array<HealthData, g_HEALTH_AMOUNT>healthArray
	{ {
		HealthData
		{
			(healthData.pos = {(g_DISPLAY_WIDTH / 2 + 2 * g_DISPLAY_WIDTH), ((g_LEVEL_HEIGHT / 2 + (g_PIXELS_PER_UNIT_DOUBLE)) - (g_ZOOL_SIZE + g_PIXELS_PER_UNIT))}),
			healthData.HalfSizeHealth
		},
		HealthData
		{
			(healthData.pos = {(g_DISPLAY_WIDTH * g_QUARTER + g_HALF_SIZE_SMALL_OBJ) , (g_LEVEL_HEIGHT * g_THREE_FIFTHS - g_PIXELS_PER_UNIT)}),
			healthData.HalfSizeHealth
		},
	} };

	for (HealthData healthConsumablesData : healthArray)
	{
		Health::Spawn(healthConsumablesData);
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

