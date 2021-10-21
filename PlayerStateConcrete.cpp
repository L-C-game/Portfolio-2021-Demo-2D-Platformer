#include "PlayerStatesConcrete.h"
#include "GameObject.h"

// Jump duration constants
// time elasped since entering jump state in frames
int jumpTime{ 0 };
// Maximum jump duration in seconds
const int jumpDuration{ 45 };

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

	if (!player->GetIsGrounded() && !Play::KeyDown(VK_SPACE))
	{
		player->SetPlayerState(FallState::getInstance());
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

	player->SetHalfSize({(Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_X_ZOOL), (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_Y_ZOOL) });

}

void IdleState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
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
	if (Play::KeyDown(VK_LEFT))
	{
		if (player->GetAcceleration().x >= 0)
		{
			const Vector2f& currentAcc = player->GetAcceleration();
			const Vector2f& acc = { -MOVEACC, (currentAcc.y) };
			player->SetIsLeftFacing(true);
			player->SetAcceleration(acc);
		}
	}

	if (Play::KeyDown(VK_RIGHT) && (player->GetPosition().x + S_PIXELS_PER_UNIT) < S_DISPLAY_WIDTH)
	{
		if (player->GetAcceleration().x <= 0)
		{
			const Vector2f& currentAcc = player->GetAcceleration();
			const Vector2f& acc = { MOVEACC, (currentAcc.y) };
			player->SetIsLeftFacing(false);
			player->SetAcceleration(acc);
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

	if (Play::KeyDown(VK_SPACE) && (player->GetIsGrounded()))
	{
		player->SetPlayerState(JumpState::getInstance());
	}

	if (!player->GetIsGrounded() && !Play::KeyDown(VK_SPACE))
	{
		player->SetPlayerState(FallState::getInstance());
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

	player->SetHalfSize({ (Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_X_ZOOL), (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_Y_ZOOL) });

}

void AccelState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(RUN_ANIM_SPEED * state.time));
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
		player->SetIsLeftFacing(true);
		player->SetPlayerState(AccelState::getInstance());
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		player->SetIsLeftFacing(false);
		player->SetPlayerState(AccelState::getInstance());
	}

	if ((abs(player->GetVelocity().x) <= MINIMUM_SPEED_RUN) && (!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)) || (Play::KeyDown(VK_LEFT) && Play::KeyDown(VK_RIGHT)))
	{
		// If the player presses neither of L and R set to idle state
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

	if (!player->GetIsGrounded() && !Play::KeyDown(VK_SPACE))
	{
		player->SetPlayerState(FallState::getInstance());
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

	player->SetHalfSize({ (Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_X_ZOOL), (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_Y_ZOOL) });
}

void DeccelState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
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

	if (!player->GetIsGrounded() && !Play::KeyDown(VK_SPACE))
	{
		player->SetPlayerState(FallState::getInstance());
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

	player->SetHalfSize({ (Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_X_ZOOL), (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_Y_ZOOL) });

}

void CrouchState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
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
	jumpTime = 0;
}

void JumpState::HandleInput(Player* player)
{
	jumpTime++;
	if(player->GetVelocity().y == 0)
	{
		Vector2f currentVel = player->GetVelocity();
		Vector2f vel = { (currentVel.x),(currentVel.y - 2) };
		player->SetVelocity(vel);
	}

	if (Play::KeyDown(VK_LEFT))
	{
		if (player->GetAcceleration().x >= 0)
		{
			const Vector2f& currentAcc = player->GetAcceleration();
			const Vector2f& acc = { -MOVEACC/2, (currentAcc.y) };
			player->SetIsLeftFacing(true);
			player->SetAcceleration(acc);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		if (player->GetAcceleration().x <= 0)
		{
			const Vector2f& currentAcc = player->GetAcceleration();
			const Vector2f& acc = { MOVEACC/2, (currentAcc.y) };
			player->SetIsLeftFacing(false);
			player->SetAcceleration(acc);
		}
	}
	else
	{
		//float acc = -(player->GetAcceleration().x);
		player->SetAcceleration({ 0.0f, player->GetAcceleration().y });
	}


	// When the player is no longer holding space and the height he is is above his initial position,
	// Change to fall state
	if (!(Play::KeyDown(VK_SPACE)) || jumpTime > jumpDuration)
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

	player->SetHalfSize({ (Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_X_ZOOL), (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_Y_ZOOL) });

}

void JumpState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
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
	player->SetIsGrounded(false);
}

void FallState::HandleInput(Player* player)
{
	Vector2f currentAcc = player->GetAcceleration();
	Vector2f acc = { (currentAcc.x),(GRAVITY) };
	player->SetAcceleration(acc);
	
	if (Play::KeyDown(VK_LEFT))
	{
		if (player->GetAcceleration().x >= 0)
		{
			const Vector2f& acc = { -MOVEACC/2, (currentAcc.y) };
			player->SetIsLeftFacing(true);
			player->SetAcceleration(acc);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		if (player->GetAcceleration().x <= 0)
		{
			const Vector2f& acc = { MOVEACC/2, (currentAcc.y) };
			player->SetIsLeftFacing(false);
			player->SetAcceleration(acc);
		}
	}
	else
	{
		player->SetAcceleration({ 0.0f, player->GetAcceleration().y });
	}

	if (player->GetIsGrounded())
	{
		player->SetPlayerState(IdleState::getInstance());
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

	player->SetHalfSize({ (Play::GetSpriteWidth(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_X_ZOOL), (Play::GetSpriteHeight(player->GetCurrentSpriteId()) / 2) - (PIXEL_EXCESS_Y_ZOOL) });

}

void FallState::DrawPlayer(const Player* player, GameState& state) const
{
	Play::DrawSprite(player->GetCurrentSpriteId(), player->GetPosition(), static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
}

void FallState::StateExit(Player* player)
{
	player->SetVelocity({ player->GetVelocity().x, (0.0f) });
}
