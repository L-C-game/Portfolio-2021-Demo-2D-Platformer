// Implementation of the player class
#include "GameObject.h"
#include "Player.h"
#include "PlayerStatesConcrete.h"

Player::Player(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_PLAYER);
	SetUpdateOrder(0);
	SetDrawOrder(0);
	SetStatic(false);

}

// Spawn player
void Player::Spawn()
{
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_PLAYER) < 1)
	{
		Point2f initialPos = { static_cast<float>(S_PIXELS_PER_UNIT_DOUBLE), static_cast<float>(S_DISPLAY_HEIGHT - (S_PIXELS_PER_UNIT_DOUBLE + S_PIXELS_PER_UNIT))};
		GameObject* playerG = new Player(initialPos);	
		Player* player = static_cast<Player*>(playerG);
		player->SetPlayerState(IdleState::getInstance());
	}
}

void Player::SetPlayerState(PlayerState& newState)
{
	m_pStateCurrent = &newState;
}

void Player::SwapPlayerState(PlayerState& newState)
{
	Player& playerAddress = *this;
	m_pStateCurrent->StateExit(playerAddress);
	m_pStateCurrent = &newState;
	m_pStateCurrent->StateEnter(playerAddress);
}

void Player::CollisionSystem()
{
	std::vector <GameObject*> oList = GameObject::GetTypeList(GameObject::Type::OBJ_ALL);
	std::vector< GameObject* > collisionList;
	collisionList.clear();
	for (GameObject* other : oList)
	{
		if (!(other->GetType() == GameObject::Type::OBJ_PLAYER))
		{
			GameObject::CollidingSide collidingSide = this->ResolveCollision(other);
			if (collidingSide != GameObject::CollidingSide::SIDE_NULL)
			{
				collisionList.push_back(other);
				// Switch case which checks what side of the player is colliding with an object
				// If the logic here becomes bloated it might be best to change it to a design pattern state machine.
   				switch (collidingSide) {
				case GameObject::CollidingSide::SIDE_UP:
					// Code
					this->SetAcceleration({ this->GetAcceleration().x, GRAVITY });
					this->SetVelocity({ this->GetVelocity().x, 0.0f });
					break;
				case GameObject::CollidingSide::SIDE_RIGHT:
					//this->SetAcceleration({ 0.0f, this->GetAcceleration().y });
					//this->SetVelocity({ 0.0f, this->GetVelocity().y });
					break;
				case GameObject::CollidingSide::SIDE_DOWN:
					this->SetIsGrounded(true);
					break;
				case GameObject::CollidingSide::SIDE_LEFT:
					if (this->GetIsLeftFacing())
					{
						this->SetAcceleration({ 0.0f, this->GetAcceleration().y });
						this->SetVelocity({ 0.0f, this->GetVelocity().y });
					}
					break;
				}
			}
		}
	}
	if (this->GetVelocity().y >= 0 && collisionList.empty())
	{
		this->SetIsGrounded(false);
	}
}

void Player::Update(GameState& state)
{
	Player& playerAddress = *this;

	SetVelocity(GetVelocity() + GetAcceleration());
	if (abs(GetVelocity().x) >= MAX_SPEED_RUN)
	{
		SetVelocity({ (GetVelocity().x / abs(GetVelocity().x)) * MAX_SPEED_RUN, GetVelocity().y });
	}
	if (abs(GetVelocity().y) >= MAX_SPEED_FALL)
	{
		SetVelocity({ GetVelocity().x, (GetVelocity().y / abs(GetVelocity().y)) * MAX_SPEED_FALL });
	}
	SetPosition(GetPosition() + GetVelocity());

	m_pStateCurrent->SetupBB(playerAddress);
	m_pStateCurrent->HandleInput(playerAddress);
	CollisionSystem();
}

void Player::Draw(GameState& state) const
{
	const Player& playerAddress = *this;
	m_pStateCurrent->DrawPlayer(playerAddress, state);
}
