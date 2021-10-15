// Implementation of the player class
#include "GameObject.h"
#include "Player.h"
#include "PlayerStatesConcrete.h"

Player::Player(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_PLAYER);
	SetUpdateOrder(0);
	SetDrawOrder(0);
	m_pStateCurrent = &IdleState::getInstance();
	SetStatic(false);
}

// Spawn player
void Player::Spawn(GameState& state)
{
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_PLAYER) < 1)
	{
		Point2f initialPos = { static_cast<float>(S_SCREEN_LIMIT), static_cast<float>(S_DISPLAY_HEIGHT - (S_SCREEN_LIMIT + S_HALF_LIMIT))};
		GameObject* player = new Player(initialPos);
					
	}
}

void Player::SetPlayerState(PlayerState& newState)
{
	m_pStateCurrent->StateExit(this);
	m_pStateCurrent = &newState;
	m_pStateCurrent->StateEnter(this);
}

void Player::Update(GameState& state)
{
	SetVelocity(GetVelocity() + GetAcceleration());
	SetPosition(GetPosition() + GetVelocity());
	m_pStateCurrent->SetupBB(this);
	m_pStateCurrent->HandleInput(this);
}

void Player::Draw(GameState& state) const
{
	m_pStateCurrent->DrawPlayer(this, state);
}
