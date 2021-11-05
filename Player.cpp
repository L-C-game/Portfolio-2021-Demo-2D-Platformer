// Implementation of the player class
#include "GameObject.h"
#include "Player.h"
#include "PlayerStatesConcrete.h"
#include "Pickup.h"
#include "Block.h"

Player::Player(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_PLAYER);
	SetUpdateOrder(0);
	SetDrawOrder(0);
	SetStatic(false);
	SetHalfSize({ (ZOOL_SIZE / 2) - (PIXEL_EXCESS_X_ZOOL), (ZOOL_SIZE / 2) - (PIXEL_EXCESS_Y_ZOOL) });
}

// Spawn player
void Player::Spawn()
{
	if (GameObject::GetObjectCount(GameObject::Type::OBJ_PLAYER) < 1)
	{
		GameObject* playerG = new Player(initialPlayerPos);
		Player* player = static_cast<Player*>(playerG);
		player->SetInitialPlayerState();
		player->SetActive(true);
	}
}

void Player::SetInitialPlayerState()
{
	PlayerState& newState = IdleState::getInstance();
	m_pStateCurrent = &newState;
}

void Player::SwapPlayerState(PlayerState& newState)
{
	Player& playerAddress = *this;
	m_pStateCurrent->StateExit(playerAddress);
	m_pStateCurrent = &newState;
	m_pStateCurrent->StateEnter(playerAddress);
}

void Player::CollisionSystem(GameState& gameState)
{
	std::vector <GameObject*> oList = GameObject::GetTypeList(GameObject::Type::OBJ_ALL);
	// To store which objects collide with the player
	std::vector< GameObject* > collisionList;
	collisionList.clear();

	// Check if any of the GameObjects have collided with the player
	for (GameObject* other : oList)
	{
		if (!(other->GetType() == GameObject::Type::OBJ_PLAYER))
		{
			// Resolve collison and return which side of the player has collided
			GameObject::CollidingSide collidingSide = ResolveCollision(other);
			if (collidingSide != GameObject::CollidingSide::SIDE_NULL)
			{
				collisionList.push_back(other);

   				switch (collidingSide) {
				case GameObject::CollidingSide::SIDE_UP:
					SetAcceleration({ GetAcceleration().x, GRAVITY });
					SetVelocity({ GetVelocity().x, 0.0f });
					break;
				case GameObject::CollidingSide::SIDE_RIGHT:
					SetAcceleration({ 0.0f, GetAcceleration().y });
					SetVelocity({ 0.0f, GetVelocity().y });
					break;
				case GameObject::CollidingSide::SIDE_DOWN:
					SetIsGrounded(true);
					break;
				case GameObject::CollidingSide::SIDE_LEFT:
					if (GetIsLeftFacing())
					{
						SetAcceleration({ 0.0f, GetAcceleration().y });
						SetVelocity({ 0.0f, GetVelocity().y });
					}
					break;
				}

				if (other->GetIsCollectable())
				{
					if (other->GetType() == GameObject::Type::OBJ_PICKUP)
					{
						Pickup* pickUp = static_cast<Pickup*>(other);
						SetScore(pickUp->GetPointValue() + GetScore());
						pickUp->SetActive(false);
					}
				}

				if (other->GetType() == GameObject::Type::OBJ_BLOCK)
				{
					Block* block = static_cast<Block*>(other);
					block->SetBlockState(Block::BlockState::BREAK_STATE);
				}

				if (other->GetType() == GameObject::Type::OBJ_SPIKE)
				{
					if (GetHealth() >= MIN_HEALTH_PLAYER && !GetIsHurt())
					{
						SetHealth(GetHealth() - 1);
						if (GetHealth() != 0)
						{
							SetIsHurt(true);
						}
						else 
						{
							SetInitialPlayerState();
						}
					}
				}
			}
		}
	}

	if (GetVelocity().y >= 0 && collisionList.empty())
	{
		SetIsGrounded(false);
	}
}

void Player::Update(GameState& gameState)
{
	// Velocity taking into account acceleration and constraining the velocity within the max speed (inclusive)
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

	//Sets the state depending on the input
	Player& playerAddress = *this;
	m_pStateCurrent->HandleInput(playerAddress);
	m_pStateCurrent->SetupBB(playerAddress);
	CollisionSystem(gameState);

	CentreCameraOnPlayer(gameState);
}

// Sets up the camera position, constrained within the bounds of the level
void Player::CentreCameraOnPlayer(GameState& gameState)
{
	// Setting the position of the camera wrt the player
	gameState.camera.pos.x = (GetPosition().x) - (gameState.camera.width / 2);
	gameState.camera.pos.y = (GetPosition().y) - (gameState.camera.height / 2);

	if (gameState.camera.pos.x < 0)
	{
		gameState.camera.pos.x = 0.0f;
	}

	if (gameState.camera.pos.y < 0)
	{
		gameState.camera.pos.y = 0.0f;
	}

	if (gameState.camera.pos.x > (LEVEL_WIDTH - gameState.camera.width))
	{
		gameState.camera.pos.x = LEVEL_WIDTH - gameState.camera.width;
	}

	if (gameState.camera.pos.y > (LEVEL_HEIGHT - gameState.camera.height))
	{
		gameState.camera.pos.y = LEVEL_HEIGHT - gameState.camera.height;
	}
}

void Player::Draw(GameState& gameState) const
{
	const Player& playerAddress = *this;
	m_pStateCurrent->DrawPlayer(playerAddress, gameState);
}
