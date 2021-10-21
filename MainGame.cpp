#include "MainGame.h"
#include "LeftBarrier.h"
#include "Floor.h"
#include "Ceiling.h"
#include "Player.h"
#include "Platform.h"
#define PLAY_IMPLEMENTATION
#include "Play.h"
#include <array>

GameState state;
PlatformData platData;

// The entry point for a Windows program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( S_DISPLAY_WIDTH, S_DISPLAY_HEIGHT, S_DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground( "Data\\Backgrounds\\Background.png" );
	// Spawn game world
	Floor::Spawn();
	LBarrier::Spawn();
	Ceiling::Spawn();
	Player::Spawn();

	std::array<Point2f, platformNumber>platformPos{ { { S_DISPLAY_WIDTH * QUARTER, (S_DISPLAY_HEIGHT - (S_DISPLAY_HEIGHT * QUARTER)) }, { S_DISPLAY_WIDTH * QUARTER, (S_DISPLAY_HEIGHT - (S_DISPLAY_HEIGHT * THREE_QUARTERS)) }, {  S_DISPLAY_WIDTH * THREE_QUARTERS, (S_DISPLAY_HEIGHT - (S_DISPLAY_HEIGHT * QUARTER)) }, { S_DISPLAY_WIDTH * THREE_QUARTERS, (S_DISPLAY_HEIGHT - (S_DISPLAY_HEIGHT * THREE_QUARTERS)) } } };
	
	for (const Point2f pos : platformPos)
	{
		PopulateWorld(pos);
	}
}

// Called by the PlayBuffer once for each frame of the game (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	// Keeping track of the elapsed time 
	state.time += elapsedTime;
	Play::DrawBackground();
	GameObject::DrawAll(state);
	Play::PresentDrawingBuffer();

	GameObject::UpdateAll(state);

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

void PopulateWorld(Point2f platPos)
{
	Platform::Spawn(platPos, platData);
}
