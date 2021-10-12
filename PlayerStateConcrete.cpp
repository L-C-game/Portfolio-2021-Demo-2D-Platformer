#include "PlayerStatesConcrete.h"

// Constant for Jump before the platforms are added
float initY = static_cast<float>(S_DISPLAY_HEIGHT - S_SCREEN_LIMIT);

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

void IdleState::DrawPlayer(const Player* player, GameState& state) const
{
	if (!(player->GetIsLeftFacing()))
	{
		Play::DrawSprite(Play::GetSpriteId("spr_zool_stand_right"), player->GetPosition(), static_cast<int>(10 * state.time));
	}

	if (player->GetIsLeftFacing())
	{
		Play::DrawSprite(Play::GetSpriteId("spr_zool_stand_left"), player->GetPosition(), static_cast<int>(10 * state.time));
	}
}

PlayerState& IdleState::getInstance()
{
	static IdleState singleton;
	return singleton;
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
			Vector2f vel = { (currentVel.x - 1),(currentVel.y) };
			player->SetIsLeftFacing(true);
			player->SetVelocity(vel);
		}
	}
	else if (Play::KeyDown(VK_RIGHT) && (player->GetPosition().x + S_HALF_LIMIT) < S_DISPLAY_WIDTH)
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
		Vector2f vel = { (0.0f),(0.0f) };
		player->SetVelocity(vel);
	}

	// Still glitches on the walls if holding both L and R

	if (!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT))
	{
		player->SetVelocity({ 0.0f, 0.0f });
		player->SetPlayerState(IdleState::getInstance());
	}
	
	if (Play::KeyDown(VK_LEFT) && Play::KeyDown(VK_RIGHT))
	{
		player->SetVelocity({ 0.0f, 0.0f });
		player->SetPlayerState(IdleState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player->SetVelocity({ 0.0f, 0.0f });
		player->SetPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE))
	{
		player->SetPlayerState(JumpState::getInstance());
	}

	// Needs to be able to fall
}

void WalkState::DrawPlayer(const Player* player, GameState& state) const
{
	if (!(player->GetIsLeftFacing()))
	{
		Play::DrawSprite(Play::GetSpriteId("spr_zool_walk_right_strip_16"), player->GetPosition(), static_cast<int>(32 * state.time));
	}
	
	if (player->GetIsLeftFacing())
	{
		Play::DrawSprite(Play::GetSpriteId("spr_zool_walk_left_strip_16"), player->GetPosition(), static_cast<int>(32 * state.time));
	}
}

PlayerState& WalkState::getInstance()
{
	static WalkState singleton;
	return singleton;
}

void CrouchState::HandleInput(Player* player)
{
	if (!(Play::KeyDown(VK_DOWN)) && (Play::KeyDown(VK_LEFT) || Play::KeyDown(VK_RIGHT)))
	{
		player->SetPlayerState(WalkState::getInstance());
	}
	else if (!(Play::KeyDown(VK_DOWN)) && (!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)))
	{
		player->SetPlayerState(IdleState::getInstance());
	}

	if ((Play::KeyDown(VK_DOWN)) && Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT))
	{
		player->SetIsLeftFacing(true);
	}

	if ((Play::KeyDown(VK_DOWN)) && Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT))
	{
		player->SetIsLeftFacing(false);
	}
}

void CrouchState::DrawPlayer(const Player* player, GameState& state) const
{
	if (!(player->GetIsLeftFacing()))
	{
		Play::DrawSprite(Play::GetSpriteId("spr_zool_crouch_right"), player->GetPosition(), static_cast<int>(10 * state.time));
	}

	if (player->GetIsLeftFacing())
	{
		Play::DrawSprite(Play::GetSpriteId("spr_zool_crouch_left"), player->GetPosition(), static_cast<int>(10 * state.time));
	}
}

PlayerState& CrouchState::getInstance()
{
	static CrouchState singleton;
	return singleton;
}

void JumpState::HandleInput(Player* player)
{
	// Changing state to falling
	if(player->GetVelocity().y == 0)
	{
		Vector2f currentVel = player->GetVelocity();
		Vector2f vel = { (currentVel.x),(currentVel.y - 2) };
		//oldPosY = pos.y;
		player->SetVelocity(vel);
	}

	if (Play::KeyDown(VK_LEFT))
	{
		if (player->GetVelocity().x >= 0)
		{
			Vector2f currentVel = player->GetVelocity();
			Vector2f vel = { (currentVel.x - 1),(currentVel.y) };
			//oldPosY = pos.y;
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
			//oldPosY = pos.y;
			player->SetIsLeftFacing(false);
			player->SetVelocity(vel);
		}
	}
	else
	{
		Vector2f currentVel = player->GetVelocity();
		Vector2f vel = { (0.0f),(currentVel.y) };
		//oldPosY = pos.y;
		player->SetVelocity(vel);
	}

	if (!(Play::KeyDown(VK_SPACE)) && player->GetPosition().y < initY - S_HALF_LIMIT)
	{
		player->SetPlayerState(FallState::getInstance());
	}

}

void JumpState::DrawPlayer(const Player* player, GameState& state) const
{
	if (!(player->GetIsLeftFacing()))
	{
		Play::DrawSprite(Play::GetSpriteId("spr_zool_jump_right"), player->GetPosition(), static_cast<int>(10 * state.time));
	}

	if (player->GetIsLeftFacing())
	{
		Play::DrawSprite(Play::GetSpriteId("spr_zool_jump_left"), player->GetPosition(), static_cast<int>(10 * state.time));
	}
}

PlayerState& JumpState::getInstance()
{
	static JumpState singleton;
	return singleton;
}

void FallState::HandleInput(Player* player)
{
	if (player->GetVelocity().y <= 0)
	{
		Vector2f currentVel = player->GetVelocity();
		Vector2f vel = { (currentVel.x),(currentVel.y + 2) };
		//oldPosY = pos.y;
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
		player->SetVelocity({ (0.0f), (0.0f) });
		player->SetIsGrounded(true);
		player->SetPlayerState(WalkState::getInstance());
	}
}

void FallState::DrawPlayer(const Player* player, GameState& state) const
{
	if (!(player->GetIsLeftFacing()))
	{
		Play::DrawSprite(Play::GetSpriteId("spr_zool_fall_right"), player->GetPosition(), static_cast<int>(10 * state.time));
	}

	if (player->GetIsLeftFacing())
	{
		Play::DrawSprite(Play::GetSpriteId("spr_zool_fall_left"), player->GetPosition(), static_cast<int>(10 * state.time));
	}
}

PlayerState& FallState::getInstance()
{
	static FallState singleton;
	return singleton;
}
