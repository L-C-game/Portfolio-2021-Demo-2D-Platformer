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
	CreateLevel();

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
		GameObject::DestroyAll();
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
		GameObject::DestroyAll();
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

void CreateLevel()
{
	if (!g_IS_LEVEL_CREATED)
	{
		PlaySpawnAll();
		LoadLevel();
	}
	g_IS_LEVEL_CREATED = true;
}

// Adapted from Baamageddon level load from file
void LoadLevel(void)
{
	std::ifstream levelfile;
	levelfile.open("ZoolLevel.txt");

	std::string sType, sX, sY, sSprite, sPValue; // Strings for the file data

	std::getline(levelfile, sType); // get the type line by line from the file

	while (!levelfile.eof()) // While not at the end of file
	{
		std::getline(levelfile, sType); // Data format within file
		std::getline(levelfile, sX);
		std::getline(levelfile, sY);
		std::getline(levelfile, sSprite);
		std::getline(levelfile, sPValue);

		if (sType == "HEALTH") // Check that the correct data is being accessed using the GameObject type name
		{
			HealthData healthData;
			
			healthData.pos = { std::stof(sX), std::stof(sY) };

			Health::Spawn(healthData);
		}

		if (sType == "SPIKE")
		{
			SpikeData spikeData;

			spikeData.pos = { std::stof(sX), std::stof(sY) };

			Spike::Spawn(spikeData);
		}

		if (sType == "BLOCK")
		{
			BlockData blockData;

			blockData.pos = { std::stof(sX), std::stof(sY) };

			Block::Spawn(blockData);
		}

		if (sType == "PICKUP")
		{
			PickUpData pickupData;

			pickupData.pos = { std::stof(sX), std::stof(sY) };
			pickupData.pickupSprite = std::stoi(sSprite);
			pickupData.pointValue = std::stoi(sPValue);

			Pickup::Spawn(pickupData);
		}

		if (sType == "PLATFORM")
		{
			PlatformData platformData;

			platformData.pos = { std::stof(sX), std::stof(sY) };
			platformData.colour = std::stoi(sSprite);

			Platform::Spawn(platformData);
		}
	}

	levelfile.close();
}

// Setting up the Game world in a data oriented way
void PlaySpawnAll()
{
	Floor::Spawn();
	Player::Spawn();
	UltimateToken::Spawn();


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

