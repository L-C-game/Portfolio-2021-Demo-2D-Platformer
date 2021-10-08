// Implementation of the player class
#include "GameObject.h"
#include "Player.h"

// Spawn player
void Player::Spawn(GameState& state)
{
	if (GameObject::s_vUpdateList.size() == 0)
	{
		//Player constructor
		if (GameObject::GetObjectCount(GameObject::Type::OBJ_PLAYER) < 1)
		{
			Point2f initialPos = {static_cast<float>(S_SCREEN_LIMIT), static_cast<float>(S_DISPLAY_HEIGHT - S_SCREEN_LIMIT)};
			GameObject* player = new Player(initialPos);
			//player->SetPlayerState(static_cast<int>(PlayerState::STATE_IDLE));			
		}
	}

}

void Player::Update(GameState& state)
{
	 /*Will have the switch case for the states*/
	 switch (GetPlayerState())
	{ 
	case static_cast<int>(PlayerState::STATE_IDLE): 
		IdleUpdate(state);
		break;
	case static_cast<int>(PlayerState::STATE_WALK):
		WalkUpdate(state);
		break;
	}
}

// Specific update functions that deal with input
void Player::IdleUpdate(GameState& state)
{
	if (Play::KeyDown(VK_LEFT) || Play::KeyDown(VK_RIGHT))
	{
		SetPlayerState(static_cast<int>(PlayerState::STATE_WALK));
	}
}

void Player::WalkUpdate(GameState& state)
{
	// Input handling
	// Allow the player to move the alien along the horizontal axis using the directional keys
	if (Play::KeyDown(VK_LEFT) && GetPosition().x > S_HALF_LIMIT)
	{
		Point2f currentPos = GetPosition();
		Point2f pos = { (currentPos.x - 1),(currentPos.y) };
		SetPosition(pos);
		SetIsLeftFacing(true);
	}

	if (Play::KeyDown(VK_RIGHT) && (GetPosition().x + S_HALF_LIMIT) < S_DISPLAY_WIDTH)
	{
		Point2f currentPos = GetPosition();
		Point2f pos = { (currentPos.x + 1),(currentPos.y) };
		SetPosition(pos);
		SetIsLeftFacing(false);
	}

	if (!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT))
	{
		SetPlayerState(static_cast<int>(PlayerState::STATE_IDLE));
	}
}

// Draw with switch case
void Player::Draw(GameState& state) const
{
	switch (GetPlayerState())
	{
	case static_cast<int>(PlayerState::STATE_IDLE):
		IdleDraw(state);
		break;
	case static_cast<int>(PlayerState::STATE_WALK):
		WalkDraw(state);
		break;
	}
}

// Specific draw functions
void Player::IdleDraw(GameState& state) const
{
	/*Play::CentreSpriteOrigin("player_idle");*/
	if (!GetIsLeftFacing())
	{
		Play::DrawSprite(Play::GetSpriteId("playerIdle_right"), GetPosition(), static_cast<int>(10 * state.time));
	}
	else if (GetIsLeftFacing())
	{
		Play::DrawSprite(Play::GetSpriteId("playerIdle_left"), GetPosition(), static_cast<int>(10 * state.time));
	}

}

void Player::WalkDraw(GameState& state) const
{
	/*Play::CentreSpriteOrigin("player_walk");*/
	if (!GetIsLeftFacing())
	{
		Play::DrawSprite(Play::GetSpriteId("playerWalk_right_3"), GetPosition(), static_cast<int>(10 * state.time));
	}
	else if (GetIsLeftFacing())
	{
		Play::DrawSprite(Play::GetSpriteId("playerWalk_left_3"), GetPosition(), static_cast<int>(10 * state.time));
	}
}