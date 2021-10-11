#include "MainGame.h"
#include "Player.h"
#define PLAY_IMPLEMENTATION
#include "Play.h"

GameState state;

// The entry point for a Windows program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( S_DISPLAY_WIDTH, S_DISPLAY_HEIGHT, S_DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground( "Data\\Backgrounds\\Background.png" );
	Player::Spawn(state);

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
