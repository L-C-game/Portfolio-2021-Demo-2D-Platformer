/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game
*/

// Implementation of the player class
#include "GameObject.h"
#include "Player.h"
#include "PlayerStatesConcrete.h"
#include "Pickup.h"
#include "Block.h"
#include "Health.h"
#include "UltimateToken.h"

Player::Player(Point2f pos) : GameObject(pos)
{
	SetType(Type::OBJ_PLAYER);
	SetUpdateOrder(updateOrder::UPDATE_ORDER_PLAYER);
	SetDrawOrder(drawOrder::DRAW_ORDER_PLAYER);
	SetHalfSize({ (g_ZOOL_SIZE / 2) - (g_PIXEL_EXCESS_X_ZOOL), (g_ZOOL_SIZE / 2) - (g_PIXEL_EXCESS_Y_ZOOL) });
}

// Spawn player
void Player::Spawn()
{
	GameObject* playerG = new Player(g_INITIAL_PLAYER_POS);
	Player* player = static_cast<Player*>(playerG);
	player->SetInitialPlayerState();
	player->SetActive(true);
}

// Used only for the initial state
void Player::SetInitialPlayerState()
{
	PlayerState& newState = IdleState::getInstance();
	m_pStateCurrent = &newState;
}

// Calls exit and entry methods and sets the state depending on which reference to the state instances is passed in
void Player::SetPlayerState(PlayerState& newState)
{
	Player& playerAddress = *this;
	m_pStateCurrent->StateExit(playerAddress);
	m_pStateCurrent = &newState;
	m_pStateCurrent->StateEnter(playerAddress);
}

void Player::ResetPlayer() // Method to reset the player to the start position and health
{
	SetPosition(g_INITIAL_PLAYER_POS);
	SetHealth(g_MAX_HEALTH_PLAYER);
	SetScore(0);
	SetAcceleration({ 0.0f, 0.0f });
	SetVelocity({ 0.0f, 0.0f });
	SetPlayerState(IdleState::getInstance());
	SetHasUltimate(false);
}

void Player::CollisionSystem()
{
	std::vector <GameObject*> oList = GameObject::GetTypeList(GameObject::Type::OBJ_ALL);
	// To store which objects collide with the player
	std::vector< GameObject* > collisionList;
	collisionList.clear();

	// Check if any of the GameObjects have collided with the player
	for (GameObject* other : oList)
	{
		// So the player isn't checked 
		if (!(other->GetType() == GameObject::Type::OBJ_PLAYER))
		{
			// Resolve collison and return which side of the player has collided
			GameObject::CollidingSide collidingSide = ResolveCollision(other);
			if (collidingSide != GameObject::CollidingSide::SIDE_NULL)
			{
				// Check whether the object is solid (if not then don't resolve collision or alter player acceleration etc
				if (other->GetSolid())
				{
					// Fill the collision list
					collisionList.push_back(other);
				

					switch (collidingSide) {
					case GameObject::CollidingSide::SIDE_UP:
						SetAcceleration({ GetAcceleration().x, g_GRAVITY });
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
				}

				// Perform different actions depending on what object is collided with by the player

				if (other->GetIsCollectable())
				{
					if (other->GetType() == GameObject::Type::OBJ_PICKUP)
					{
						Play::PlayAudio("pickUp");
						Pickup* pickUp = static_cast<Pickup*>(other);
						SetScore(pickUp->GetPointValue() + GetScore());
						pickUp->SetActive(false);
					}
				}

				if (other->GetType() == GameObject::Type::OBJ_BLOCK)
				{
					Block* block = static_cast<Block*>(other);
					if (block->GetBlockState() == Block::BlockState::STABLE_STATE)
					{
						Play::PlayAudio("blockBreak");
						block->SetBlockState(Block::BlockState::BREAK_STATE); 
					}
				}

				if (other->GetType() == GameObject::Type::OBJ_SPIKE)
				{
					if (GetHealth() >= g_MIN_HEALTH_PLAYER && !GetIsHurt())
					{
						SetHealth(GetHealth() - 1);
						if (GetHealth() > 0)
						{
							Play::PlayAudio("hitPlayer");
							SetIsHurt(true);
						}
						else 
						{
							Play::StopAudioLoop("untitled");
							Play::StartAudioLoop("weirdWavvyThing");
							SetGameStatusState(GameStatusState::GAMEOVER_STATE);
						}
					}
				}

				if (other->GetType() == GameObject::Type::OBJ_HEALTH)
				{
					if (GetHealth() < g_MAX_HEALTH_PLAYER)
					{
						Health* health = static_cast<Health*>(other);
						SetHealth(GetHealth() + 1);
						Play::PlayAudio("heal");
						health->SetActive(false);
					}
				}

				if (other->GetType() == GameObject::Type::OBJ_ULTIMATE)
				{
					UltimateToken* ultimateToken = static_cast<UltimateToken*>(other);
					SetHasUltimate(true);
					ultimateToken->SetActive(false);
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
	if (abs(GetVelocity().x) >= g_MAX_SPEED_RUN)
	{
		SetVelocity({ (GetVelocity().x / abs(GetVelocity().x)) * g_MAX_SPEED_RUN, GetVelocity().y });
	}
	if (abs(GetVelocity().y) >= g_MAX_SPEED_FALL)
	{
		SetVelocity({ GetVelocity().x, (GetVelocity().y / abs(GetVelocity().y)) * g_MAX_SPEED_FALL });
	}
	SetPosition(GetPosition() + GetVelocity());

	//Sets the state depending on the input
	Player& playerAddress = *this;
	m_pStateCurrent->HandleInput(playerAddress);
	m_pStateCurrent->SetupAnim(playerAddress);
	// Check for collisions and perform the appropriate functionality depending on the object collided with
	CollisionSystem();

	CentreCameraOnPlayer(gameState);
}

// Sets up the camera position, constrained within the bounds of the g_LEVEL
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

	if (gameState.camera.pos.x > (g_LEVEL_WIDTH - gameState.camera.width))
	{
		gameState.camera.pos.x = g_LEVEL_WIDTH - gameState.camera.width;
	}

	if (gameState.camera.pos.y > (g_LEVEL_HEIGHT - gameState.camera.height))
	{
		gameState.camera.pos.y = g_LEVEL_HEIGHT - gameState.camera.height;
	}
}

void Player::Draw(GameState& gameState) const
{
	const Player& playerAddress = *this;
	m_pStateCurrent->DrawPlayer(playerAddress, gameState);
}
