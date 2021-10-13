#include "PlayerStatesConcrete.h"

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
	player->SetVelocity({ 0.0f, 0.0f });
}

void IdleState::HandleInput(Player* player)
{
	if ((Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT)) || (Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)))
	{
		player->SetPlayerState(WalkState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player->SetPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE))
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

	player->SetHalfSize({ Play::GetSpriteWidth(player->GetCurrentSpriteId())/2, Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2 });

}

void IdleState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(10 * state.time));
}

void IdleState::StateExit(Player* player)
{

}

// WalkState
PlayerState& WalkState::getInstance()
{
	static WalkState singleton;
	return singleton;
}

void WalkState::StateEnter(Player* player)
{

}

void WalkState::HandleInput(Player* player)
{
	// Input handling
	// Allow the player to move Zool along the horizontal axis using the directional keys
	if (player->GetVelocity().x == 0)
	{
		Vector2f currentVel = player->GetVelocity();
		Vector2f vel = { (currentVel.x),(currentVel.y) };
		player->SetVelocity(vel);
	}

	if (Play::KeyDown(VK_LEFT) && player->GetPosition().x > S_HALF_LIMIT)
	{
		if (player->GetVelocity().x >= 0)
		{
			Vector2f currentVel = player->GetVelocity();
			Vector2f vel = { (currentVel.x - 2),(currentVel.y) };
			player->SetIsLeftFacing(true);
			player->SetVelocity(vel);
		}
	}
	else if (Play::KeyDown(VK_RIGHT) && (player->GetPosition().x + S_HALF_LIMIT) < S_DISPLAY_WIDTH)
	{
		if (player->GetVelocity().x <= 0)
		{
			Vector2f currentVel = player->GetVelocity();
			Vector2f vel = { (currentVel.x + 2),(currentVel.y) };
			player->SetIsLeftFacing(false);
			player->SetVelocity(vel);
		}
	}
	else
	{
		Vector2f currentVel = player->GetVelocity();
		Vector2f vel = { (0.0f),(0.0f) };
		player->SetVelocity(vel);
	}

	if ((!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)) || (Play::KeyDown(VK_LEFT) && Play::KeyDown(VK_RIGHT)))
	{
		// If the player presses neither of L and R, or presses L and R at once then we change from walk to Idle
		player->SetPlayerState(IdleState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player->SetPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE))
	{
		player->SetPlayerState(JumpState::getInstance());
	}
}

void WalkState::SetupBB(Player* player)
{
	if (!(player->GetIsLeftFacing()))
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_walk_right_strip_16"));
	}

	if (player->GetIsLeftFacing())
	{
		player->SetCurrentSpriteId(Play::GetSpriteId("spr_zool_walk_left_strip_16"));
	}

	player->SetHalfSize({ Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2, Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2 });

}

void WalkState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(32 * state.time));
}

void WalkState::StateExit(Player* player)
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
	player->SetVelocity({ 0.0f, 0.0f });
}

void CrouchState::HandleInput(Player* player)
{
	// Leave crouch state for the relevant input
	if (!(Play::KeyDown(VK_DOWN)) && (Play::KeyDown(VK_LEFT) || Play::KeyDown(VK_RIGHT)))
	{
		player->SetPlayerState(WalkState::getInstance());
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

	player->SetHalfSize({ Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2, Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2 });

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

	player->SetHalfSize({ Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2, Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2 });

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
	if (player->GetVelocity().y <= 0)
	{
		Vector2f currentVel = player->GetVelocity();
		Vector2f vel = { (currentVel.x),(currentVel.y + 2) };
		player->SetVelocity(vel);
	}

	
	if (Play::KeyDown(VK_LEFT))
	{
		if (player->GetVelocity().x >= 0)
		{
			Point2f currentPos = player->GetPosition();
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
			Point2f currentPos = player->GetPosition();
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

	if (player->GetPosition().y == initY)
	{
		player->SetPosition({ player->GetPosition().x, initY });
		player->SetIsGrounded(true);
		player->SetPlayerState(WalkState::getInstance());
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

	player->SetHalfSize({ Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2, Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2 });

}

void FallState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(10 * state.time));
}

void FallState::StateExit(Player* player)
{
	player->SetVelocity({ (0.0f), (0.0f) });
}
