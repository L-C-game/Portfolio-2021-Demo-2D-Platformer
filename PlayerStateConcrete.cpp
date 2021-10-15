#include "PlayerStatesConcrete.h"
#include "Floor.h"
#include "LeftBarrier.h"

// Constant for controlling Jump before the collisions and gravity are added
float initY = static_cast<float>(S_DISPLAY_HEIGHT - (S_SCREEN_LIMIT + S_HALF_LIMIT));

// IdleState
PlayerState& IdleState::getInstance()
{
	static IdleState singleton;
	return singleton;
}

void IdleState::StateEnter(Player* player)
{
	// Making sure the player comes to a complete stop when idle 
	// So the velocity doesn't carry over from the previous state
	player->SetAcceleration({ 0.0f, 0.0f});
	player->SetVelocity({ 0.0f, 0.0f });
}

void IdleState::HandleInput(Player* player)
{
	if ((Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT)) || (Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)))
	{
		player->SetPlayerState(AccelState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player->SetPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE) && (player->GetIsGrounded() == true))
	{
		player->SetPlayerState(JumpState::getInstance());
	}
}

void IdleState::SetupBB(Player* player)
{
	if (!(player->GetIsLeftFacing()))
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_stand_right"));
	}

	if (player->GetIsLeftFacing())
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_stand_left"));
	}

	player->SetHalfSize({(Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER, (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER});

}

void IdleState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(10 * state.time));
}

void IdleState::StateExit(Player* player)
{

}

// WalkState
PlayerState& AccelState::getInstance()
{
	static AccelState singleton;
	return singleton;
}

void AccelState::StateEnter(Player* player)
{

}

void AccelState::HandleInput(Player* player)
{
	// Input handling
	// Allow the player to move Zool along the horizontal axis using the directional keys
	/*if (player->GetAcceleration().x >= 0)
	{
		Vector2f currentAcc = player->GetAcceleration();
		Vector2f acc = { (currentAcc.x),(currentAcc.y) };
		player->SetAcceleration(acc);
	}*/

	std::vector<GameObject*> lBarriers = GameObject::GetTypeList(GameObject::Type::OBJ_LBARRIER);
	for (GameObject* l : lBarriers)
	{
		LBarrier* lbarrier = static_cast<LBarrier*>(l);

		if (Play::KeyDown(VK_LEFT) && !player->AABBCollision(lbarrier))
		{
			if (player->GetAcceleration().x >= 0)
			{
				Vector2f currentAcc = player->GetAcceleration();
				Vector2f acc = { (-(2.0f)/(60.0f)),(currentAcc.y) };
				player->SetIsLeftFacing(true);
				player->SetAcceleration(acc);
			}
		}
		else if (Play::KeyDown(VK_RIGHT) && (player->GetPosition().x + S_HALF_LIMIT) < S_DISPLAY_WIDTH)
		{
			if (player->GetAcceleration().x <= 0)
			{
				Vector2f currentAcc = player->GetAcceleration();
				Vector2f acc = {(2.0f)/(60.0f),(currentAcc.y) };
				player->SetIsLeftFacing(false);
				player->SetAcceleration(acc);
			}
		}
	}

	if ((!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)) || (Play::KeyDown(VK_LEFT) && Play::KeyDown(VK_RIGHT)))
	{
		// If the player presses neither of L and R set to Deccelerate state
		player->SetPlayerState(DeccelState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player->SetPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE) && (player->GetIsGrounded() == true))
	{
		player->SetPlayerState(JumpState::getInstance());
	}
}

void AccelState::SetupBB(Player* player)
{
	if (!(player->GetIsLeftFacing()))
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_walk_right_strip_16"));
	}

	if (player->GetIsLeftFacing())
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_walk_left_strip_16"));
	}

	player->SetHalfSize({ (Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER, (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER });

}

void AccelState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(32 * state.time));
}

void AccelState::StateExit(Player* player)
{

}

// Decceleration State
PlayerState& DeccelState::getInstance()
{
	static DeccelState singleton;
	return singleton;
}

void DeccelState::StateEnter(Player* player)
{
	float acc = -(player->GetAcceleration().x);
	player->SetAcceleration({ acc, player->GetAcceleration().y });
}

void DeccelState::HandleInput(Player* player)
{
	if (Play::KeyDown(VK_LEFT))
	{
		player->SetPlayerState(AccelState::getInstance());
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		player->SetPlayerState(AccelState::getInstance());
	}

	if ((abs(player->GetVelocity().x) <= 0.1f) && (!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)) || (Play::KeyDown(VK_LEFT) && Play::KeyDown(VK_RIGHT)))
	{
		// If the player presses neither of L and R set to Deccelerate state
		player->SetPlayerState(IdleState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player->SetPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE) && (player->GetIsGrounded() == true))
	{
		player->SetPlayerState(JumpState::getInstance());
	}
}

void DeccelState::SetupBB(Player* player)
{
	if (!(player->GetIsLeftFacing()))
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_skid_right"));
	}

	if (player->GetIsLeftFacing())
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_skid_left"));
	}

	player->SetHalfSize({ (Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER, (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER });
}

void DeccelState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(10 * state.time));
}

void DeccelState::StateExit(Player* player)
{

}

// CrouchState
PlayerState& CrouchState::getInstance()
{
	static CrouchState singleton;
	return singleton;
}

void CrouchState::StateEnter(Player* player)
{
	// Also don't want any movement to be carried over into the crouch state
	player->SetAcceleration({ 0.0f, 0.0f });
	player->SetVelocity({ 0.0f, 0.0f });
}

void CrouchState::HandleInput(Player* player)
{
	// Leave crouch state for the relevant input
	if (!(Play::KeyDown(VK_DOWN)) && (Play::KeyDown(VK_LEFT) || Play::KeyDown(VK_RIGHT)))
	{
		player->SetPlayerState(AccelState::getInstance());
	}
	else if (!(Play::KeyDown(VK_DOWN)) && (!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)))
	{
		player->SetPlayerState(IdleState::getInstance());
	}

	// Can change facing direction while crouched
	if ((Play::KeyDown(VK_DOWN)) && Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT))
	{
		player->SetIsLeftFacing(true);
	}

	if ((Play::KeyDown(VK_DOWN)) && Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT))
	{
		player->SetIsLeftFacing(false);
	}
}

void CrouchState::SetupBB(Player* player)
{
	if (!(player->GetIsLeftFacing()))
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_crouch_right"));
	}

	if (player->GetIsLeftFacing())
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_crouch_left"));
	}

	player->SetHalfSize({ (Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER, (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER });

}

void CrouchState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(10 * state.time));
}

void CrouchState::StateExit(Player* player)
{

}

// JumpState
PlayerState& JumpState::getInstance()
{
	static JumpState singleton;
	return singleton;
}

void JumpState::StateEnter(Player* player)
{
	player->SetIsGrounded(false);
}

void JumpState::HandleInput(Player* player)
{
	if(player->GetVelocity().y == 0)
	{
		Vector2f currentVel = player->GetVelocity();
		Vector2f vel = { (currentVel.x),(currentVel.y - 2) };
		player->SetVelocity(vel);
	}

	if (Play::KeyDown(VK_LEFT))
	{
		if (player->GetVelocity().x >= 0)
		{
			Vector2f currentVel = player->GetVelocity();
			Vector2f vel = { (currentVel.x - 1),(currentVel.y) };
			player->SetIsLeftFacing(true);
			player->SetVelocity(vel);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		if (player->GetVelocity().x <= 0)
		{
			Vector2f currentVel = player->GetVelocity();
			Vector2f vel = { (currentVel.x + 1),(currentVel.y) };
			player->SetIsLeftFacing(false);
			player->SetVelocity(vel);
		}
	}
	else
	{
		Vector2f currentVel = player->GetVelocity();
		Vector2f vel = { (0.0f),(currentVel.y) };
		player->SetVelocity(vel);
	}

	// When the player is no longer holding space and the height he is is above his initial position,
	// Change to fall state
	if (!(Play::KeyDown(VK_SPACE)) && player->GetPosition().y < initY - S_HALF_LIMIT)
	{
		player->SetPlayerState(FallState::getInstance());
	}

}

void JumpState::SetupBB(Player* player)
{
	if (!(player->GetIsLeftFacing()))
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_jump_right"));
	}

	if (player->GetIsLeftFacing())
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_jump_left"));
	}

	player->SetHalfSize({ (Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER, (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER });

}

void JumpState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(10 * state.time));
}

void JumpState::StateExit(Player* player)
{

}

// FallState
PlayerState& FallState::getInstance()
{
	static FallState singleton;
	return singleton;
}

void FallState::StateEnter(Player* player)
{

}

void FallState::HandleInput(Player* player)
{
	Vector2f currentVel = player->GetVelocity();
	Vector2f vel = { (currentVel.x),(currentVel.y + GRAVITY) };
	player->SetVelocity(vel);
	
	if (Play::KeyDown(VK_LEFT))
	{
		if (player->GetVelocity().x >= 0)
		{
			Point2f currentPos = player->GetPosition();
			Vector2f currentVel = player->GetVelocity();
			Vector2f vel = { (currentVel.x - 0.5f),(currentVel.y) };
			player->SetIsLeftFacing(true);
			player->SetVelocity(vel);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{

		if (player->GetVelocity().x <= 0)
		{
			Point2f currentPos = player->GetPosition();
			Vector2f currentVel = player->GetVelocity();
			Vector2f vel = { (currentVel.x + 0.5f),(currentVel.y) };
			player->SetIsLeftFacing(false);
			player->SetVelocity(vel);
		}
	}
	else
	{
		Vector2f currentVel = player->GetVelocity();
		Vector2f vel = { (0.0f),(currentVel.y) };
		player->SetVelocity(vel);
	}

	std::vector<GameObject*> floors = GameObject::GetTypeList(GameObject::Type::OBJ_FLOOR);
	for (GameObject* f : floors)
	{
		Floor* floor = static_cast<Floor*>(f);
		if (player->AABBCollision(floor))
		{
			player->SetPosition({ player->GetPosition().x, initY });
			player->SetIsGrounded(true);
			player->SetPlayerState(AccelState::getInstance());
		}
	}
}

void FallState::SetupBB(Player* player)
{
	if (!(player->GetIsLeftFacing()))
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_fall_right"));
	}

	if (player->GetIsLeftFacing())
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_fall_left"));
	}

	player->SetHalfSize({ (Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER, (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) + PIXEL_BUFFER });

}

void FallState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(10 * state.time));
}

void FallState::StateExit(Player* player)
{
	player->SetVelocity({ (0.0f), (0.0f) });
}
