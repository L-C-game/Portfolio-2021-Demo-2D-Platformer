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
	Play::CreateManager( S_DISPLAY_WIDTH, S_DISPLAY_HEIGHT, S_DISPLAY_SCALE );
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
		TitleStateUpdate(gameState);
		break;
	case GameStatusState::PLAY_STATE:
		PlayStateUpdate(gameState);
		GameObject::UpdateAll(gameState);
		break;
	case GameStatusState::GAMEOVER_STATE:
		GameOverStateUpdate(gameState);
		break;
	case GameStatusState::WIN_STATE:
		WinStateUpdate(gameState);
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

			if (player->GetHasUltimate())
			{
				Play::StopAudioLoop("untitled");
				Play::StartAudioLoop("HET");
				SetGameStatusState(GameStatusState::WIN_STATE);
			}
		}
	}

	Play::DrawFontText("font24px", "HEALTH: " + std::to_string(gameState.health),
		{ S_DISPLAY_WIDTH * FOUR_FIFTHS,  S_DISPLAY_HEIGHT * TENTH }, Play::CENTRE);

	if (gameState.health == 0)
	{
		Play::StopAudioLoop("untitled");
		Play::StartAudioLoop("weirdWavvyThing");
		SetGameStatusState(GameStatusState::GAMEOVER_STATE);
	}
}

void GameOverStateUpdate(GameState& gameState)
{

	if (Play::KeyPressed(VK_RETURN))
	{
		Play::StopAudioLoop("weirdWavvyThing");
		Play::StartAudioLoop("untitled");
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

void WinStateUpdate(GameState& gameState)
{

	if (Play::KeyPressed(VK_RETURN))
	{
		Play::StopAudioLoop("HET");
		Play::StartAudioLoop("untitled");
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
		{ S_DISPLAY_WIDTH / 2,  S_DISPLAY_HEIGHT * TENTH }, Play::CENTRE);

	Play::DrawFontText("font24px", "FINAL SCORE: " + std::to_string(gameState.score),
		{ S_DISPLAY_WIDTH / 2 ,  S_DISPLAY_HEIGHT * TWO_FIFTHS }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS RETURN/ENTER TO RETRY!",
		{ S_DISPLAY_WIDTH / 2,  S_DISPLAY_HEIGHT / 2 }, Play::CENTRE);

	Play::DrawFontText("font24px", "PRESS ESCAPE TO QUIT.",
		{ S_DISPLAY_WIDTH / 2,  S_DISPLAY_HEIGHT * THREE_FIFTHS }, Play::CENTRE);
}

// Setting up the Game world in a data oriented way
void PlaySpawnAll(GameState& gameState)
{
	Floor::Spawn();
	Player::Spawn();
	UltimateToken::Spawn();

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
			(platData.colour = platYellowpng)
		},
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH * 2), (LEVEL_HEIGHT / 2)}),
			platData.HalfSizePlat,
			(platData.colour = platYellowpng)
		},
		PlatformData
		{
			(platData.pos = {((S_DISPLAY_WIDTH / 2) - (S_DISPLAY_WIDTH * QUARTER)), (S_DISPLAY_HEIGHT + (S_DISPLAY_HEIGHT * QUARTER))}),
			platData.HalfSizePlat,
			(platData.colour = platPinkpng)
		},
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH / 2), (S_DISPLAY_HEIGHT)}),
			platData.HalfSizePlat,
			(platData.colour = platBluepng)
		},
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH/ 2 + S_DISPLAY_WIDTH * QUARTER), (S_DISPLAY_HEIGHT)}),
			platData.HalfSizePlat,
			(platData.colour = platRedpng)
		},
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH), (S_DISPLAY_HEIGHT - S_PIXELS_PER_UNIT_DOUBLE)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
		PlatformData
		{
			(platData.pos = {((S_DISPLAY_WIDTH) + (S_DISPLAY_WIDTH * QUARTER)), (S_DISPLAY_HEIGHT - S_PIXELS_PER_UNIT_DOUBLE)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
		PlatformData
		{
			(platData.pos = {((S_DISPLAY_WIDTH) + (S_DISPLAY_WIDTH / 2)), (S_DISPLAY_HEIGHT - S_PIXELS_PER_UNIT_DOUBLE)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
		PlatformData
		{
			(platData.pos = {((S_DISPLAY_WIDTH) + (S_DISPLAY_WIDTH * THREE_QUARTERS)), (S_DISPLAY_HEIGHT - S_PIXELS_PER_UNIT_DOUBLE)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
		PlatformData
		{
			(platData.pos = {(S_DISPLAY_WIDTH * 2), (S_DISPLAY_HEIGHT - S_PIXELS_PER_UNIT_DOUBLE)}),
			platData.HalfSizePlat,
			(platData.colour = platSpecialpng)
		},
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


		// Easter egg for Zool's 30year anniversary next year
		// START OF Z
		PickUpData
		{
			(pickUpData.pos = {Z_LEFT_X, (LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {Z_MIDDLE_X, (LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {Z_RIGHT_X, (LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},

		PickUpData
		{
			(pickUpData.pos = {Z_DIAGONAL_LEFT_X, (LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {Z_DIAGONAL_RIGHT_X, (LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},

		PickUpData
		{
			(pickUpData.pos = {Z_LEFT_X, (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(Z_MIDDLE_X), (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(Z_RIGHT_X), (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		// END OF Z
		// START OF O 
		PickUpData 
		{
			(pickUpData.pos = {(O_FIRST_LEFT_X), (LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(O_FIRST_MIDDLE_X), (LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(O_FIRST_RIGHT_X), (LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},

		PickUpData 
		{
			(pickUpData.pos = {(O_FIRST_LEFT_X), (LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(O_FIRST_LEFT_X), (LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},

		PickUpData 
		{
			(pickUpData.pos = {(O_FIRST_RIGHT_X), (LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(O_FIRST_RIGHT_X), (LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},

		PickUpData 
		{
			(pickUpData.pos = {(O_FIRST_LEFT_X), (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(O_FIRST_MIDDLE_X), (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(O_FIRST_RIGHT_X), (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		// END OF O
		// START OF O 
		PickUpData 
		{
			(pickUpData.pos = {(O_SECOND_LEFT_X), (LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(O_SECOND_MIDDLE_X), (LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(O_SECOND_RIGHT_X), (LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},

		PickUpData 
		{
			(pickUpData.pos = {(O_SECOND_LEFT_X), (LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(O_SECOND_LEFT_X), (LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(O_SECOND_RIGHT_X), (LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(O_SECOND_RIGHT_X), (LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(O_SECOND_LEFT_X), (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(O_SECOND_MIDDLE_X), (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(O_SECOND_RIGHT_X), (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		// END OF O
		// START OF L
		PickUpData 
		{
			(pickUpData.pos = {(L_LEFT_X), (LETTER_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(L_LEFT_X), (LETTER_MIDDLE_TOP_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(L_LEFT_X), (LETTER_MIDDLE_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData 
		{
			(pickUpData.pos = {(L_LEFT_X), (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(L_MIDDLE_X), (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		PickUpData
		{
			(pickUpData.pos = {(L_RIGHT_X), (LETTER_BOTTOM_Y)}),
			pickUpData.HalfSizePickUp,
			(pickUpData.pickupSprite = thirtypointpng),
			(pickUpData.pointValue = THIRTY_POINTS)
		},
		// END OF L
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

		// Second section of falling blocks
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH * QUARTER + 2 * S_DISPLAY_WIDTH), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (2 * ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH * QUARTER + 2 * S_DISPLAY_WIDTH + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (2 * ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH / 2 + 2 * S_DISPLAY_WIDTH), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH / 2 + 2 * S_DISPLAY_WIDTH + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH * THREE_QUARTERS + 2 * S_DISPLAY_WIDTH), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - ( 2 * ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH * THREE_QUARTERS + 2 * S_DISPLAY_WIDTH + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (2 * ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH), ((LEVEL_HEIGHT * THREE_QUARTERS + (S_PIXELS_PER_UNIT_DOUBLE)) + (2 * ZOOL_SIZE))}),
			blockData.HalfSizeBlock,
			(blockData.blockSprite = blockpng),
		},
		BlockData
		{
			(blockData.pos = {(S_DISPLAY_WIDTH + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT * THREE_QUARTERS + (S_PIXELS_PER_UNIT_DOUBLE)) + (2 * ZOOL_SIZE))}),
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

		// Second set of spikes
		SpikeData
		{
			(spikeData.pos = {(2 * S_DISPLAY_WIDTH), ((LEVEL_HEIGHT)-(2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * S_DISPLAY_WIDTH + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT)-(2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * S_DISPLAY_WIDTH + S_DISPLAY_WIDTH * QUARTER), ((LEVEL_HEIGHT)-(2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * S_DISPLAY_WIDTH + (S_DISPLAY_WIDTH * QUARTER) + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT)-(2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * S_DISPLAY_WIDTH + (S_DISPLAY_WIDTH / 2)), ((LEVEL_HEIGHT)-(2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * S_DISPLAY_WIDTH + (S_DISPLAY_WIDTH / 2) + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT)-(2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * S_DISPLAY_WIDTH + (S_DISPLAY_WIDTH * THREE_QUARTERS)), ((LEVEL_HEIGHT)-(2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
		SpikeData
		{
			(spikeData.pos = {(2 * S_DISPLAY_WIDTH + (S_DISPLAY_WIDTH * THREE_QUARTERS) + S_PIXELS_PER_UNIT), ((LEVEL_HEIGHT)-(2 * (ZOOL_SIZE)-(S_PIXELS_PER_UNIT)))}),
			spikeData.HalfSizeSpike
		},
	} };

	for (SpikeData spikeData : spikeArray)
	{
		Spike::Spawn(spikeData);
	}

	std::array<HealthData, HEALTH_AMOUNT>healthArray
	{ {
		HealthData
		{
			(healthData.pos = {(S_DISPLAY_WIDTH / 2 + 2 * S_DISPLAY_WIDTH), ((LEVEL_HEIGHT / 2 + (S_PIXELS_PER_UNIT_DOUBLE)) - (ZOOL_SIZE + S_PIXELS_PER_UNIT))}),
			healthData.HalfSizeHealth
		},
		HealthData
		{
			(healthData.pos = {(S_DISPLAY_WIDTH * QUARTER + HALF_SIZE_SMALL_OBJ) , (LEVEL_HEIGHT * THREE_FIFTHS - S_PIXELS_PER_UNIT)}),
			healthData.HalfSizeHealth
		},
	} };

	for (HealthData healthData : healthArray)
	{
		Health::Spawn(healthData);
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

