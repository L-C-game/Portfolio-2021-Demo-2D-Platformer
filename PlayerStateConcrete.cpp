#include "PlayerStatesConcrete.h"
#include "GameObject.h"

// Jump duration constants
// time elasped since entering jump state in frames
int jumpTime{ 0 };
// Maximum jump duration in seconds
const int jumpDuration{ 45 };

// IdleStatePlay::GetSpriteHeight(player.GetCurrentSpriteId())
PlayerState& IdleState::getInstance()
{
	static IdleState singleton;
	return singleton;
}

void IdleState::StateEnter(Player& player)
{
	// Making sure the player comes to a complete stop when idle 
	// So the velocity doesn't carry over from the previous state
	player.SetAcceleration({ 0.0f, 0.0f});
	player.SetVelocity({ 0.0f, 0.0f });
}

void IdleState::HandleInput(Player& player)
{
	if ((Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT)) || (Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)))
	{
		player.SwapPlayerState(WalkState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player.SwapPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE) && (player.GetIsGrounded()))
	{
		player.SwapPlayerState(JumpState::getInstance());
	}

	if (!player.GetIsGrounded())
	{
		player.SwapPlayerState(FallState::getInstance());
	}
}

void IdleState::DrawPlayer(const Player& player, GameState& state) const
{
	float correctedX = player.GetPosition().x - state.camera.pos.x;
	float correctedY = player.GetPosition().y - state.camera.pos.y;

	if (!(player.GetIsLeftFacing()))
	{
		Play::DrawSprite(zoolIdleRpng, { correctedX, correctedY }, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
	}

	if (player.GetIsLeftFacing())
	{
		Play::DrawSprite(zoolIdleLpng, { correctedX, correctedY }, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
	}
}

void IdleState::StateExit(Player& player)
{

}

// WalkState
PlayerState& WalkState::getInstance()
{
	static WalkState singleton;
	return singleton;
}

void WalkState::StateEnter(Player& player)
{

}

void WalkState::HandleInput(Player& player)
{
	// Input handling
	if (Play::KeyDown(VK_LEFT))
	{
		if (player.GetAcceleration().x >= 0)
		{
			const Vector2f& currentAcc = player.GetAcceleration();
			const Vector2f& acc = { -MOVEACC, (currentAcc.y) };
			player.SetIsLeftFacing(true);
			player.SetAcceleration(acc);
		}
	}

	if (Play::KeyDown(VK_RIGHT))
	{
		if (player.GetAcceleration().x <= 0)
		{
			const Vector2f& currentAcc = player.GetAcceleration();
			const Vector2f& acc = { MOVEACC, (currentAcc.y) };
			player.SetIsLeftFacing(false);
			player.SetAcceleration(acc);
		}
	}

	if ((!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)) || (Play::KeyDown(VK_LEFT) && Play::KeyDown(VK_RIGHT)))
	{
		// If the player presses neither of L and R set to Deccelerate state
		player.SwapPlayerState(SkidState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player.SwapPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE) && (player.GetIsGrounded()))
	{
		player.SwapPlayerState(JumpState::getInstance());
	}

	if (!player.GetIsGrounded())
	{
		player.SwapPlayerState(FallState::getInstance());
	}
}

void WalkState::DrawPlayer(const Player& player, GameState& state) const
{
	float correctedX = player.GetPosition().x - state.camera.pos.x;
	float correctedY = player.GetPosition().y - state.camera.pos.y;

	if (!(player.GetIsLeftFacing()))
	{
		Play::DrawSprite(zoolWalkRpng, { correctedX, correctedY }, static_cast<int>(RUN_ANIM_SPEED * state.time));
	}

	if (player.GetIsLeftFacing())
	{
		Play::DrawSprite(zoolWalkLpng, { correctedX, correctedY }, static_cast<int>(RUN_ANIM_SPEED * state.time));
	}
}

void WalkState::StateExit(Player& player)
{

}

// Decceleration State
PlayerState& SkidState::getInstance()
{
	static SkidState singleton;
	return singleton;
}

void SkidState::StateEnter(Player& player)
{
	float acc = -(player.GetAcceleration().x);
	player.SetAcceleration({ acc, player.GetAcceleration().y });
}

void SkidState::HandleInput(Player& player)
{
	if (Play::KeyDown(VK_LEFT))
	{
		player.SetIsLeftFacing(true);
		player.SwapPlayerState(WalkState::getInstance());
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		player.SetIsLeftFacing(false);
		player.SwapPlayerState(WalkState::getInstance());
	}

	if ((abs(player.GetVelocity().x) <= MINIMUM_SPEED_RUN) && (!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)) || (Play::KeyDown(VK_LEFT) && Play::KeyDown(VK_RIGHT)))
	{
		// If the player presses neither of L and R set to idle state
		player.SwapPlayerState(IdleState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player.SwapPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE) && (player.GetIsGrounded()))
	{
		player.SwapPlayerState(JumpState::getInstance());
	}

	if (!player.GetIsGrounded() && player.GetVelocity().y <= 0.0f)
	{
		player.SwapPlayerState(FallState::getInstance());
	}
}

void SkidState::DrawPlayer(const Player& player, GameState& state) const
{
	float correctedX = player.GetPosition().x - state.camera.pos.x;
	float correctedY = player.GetPosition().y - state.camera.pos.y;

	if (!(player.GetIsLeftFacing()))
	{
		Play::DrawSprite(zoolSkidRpng, { correctedX, correctedY }, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
	}

	if (player.GetIsLeftFacing())
	{
		Play::DrawSprite(zoolSkidLpng, { correctedX, correctedY }, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
	}
}

void SkidState::StateExit(Player& player)
{

}

// CrouchState
PlayerState& CrouchState::getInstance()
{
	static CrouchState singleton;
	return singleton;
}

void CrouchState::StateEnter(Player& player)
{
	// Also don't want any movement to be carried over into the crouch state
	player.SetAcceleration({ 0.0f, 0.0f });
	player.SetVelocity({ 0.0f, 0.0f });
}

void CrouchState::HandleInput(Player& player)
{
	// Leave crouch state for the relevant input
	if (!(Play::KeyDown(VK_DOWN)) && (Play::KeyDown(VK_LEFT) || Play::KeyDown(VK_RIGHT)))
	{
		player.SwapPlayerState(WalkState::getInstance());
	}
	else if (!(Play::KeyDown(VK_DOWN)) && (!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)))
	{
		player.SwapPlayerState(IdleState::getInstance());
	}

	// Can change facing direction while crouched
	if ((Play::KeyDown(VK_DOWN)) && Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT))
	{
		player.SetIsLeftFacing(true);
	}

	if ((Play::KeyDown(VK_DOWN)) && Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT))
	{
		player.SetIsLeftFacing(false);
	}

}

void CrouchState::DrawPlayer(const Player& player, GameState& state) const
{
	float correctedX = player.GetPosition().x - state.camera.pos.x;
	float correctedY = player.GetPosition().y - state.camera.pos.y;

	if (!(player.GetIsLeftFacing()))
	{
		Play::DrawSprite(zoolCrouchRpng, { correctedX, correctedY }, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
	}

	if (player.GetIsLeftFacing())
	{
		Play::DrawSprite(zoolCrouchLpng, { correctedX, correctedY }, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
	}
}

void CrouchState::StateExit(Player& player)
{

}

// JumpState
PlayerState& JumpState::getInstance()
{
	static JumpState singleton;
	return singleton;
}

void JumpState::StateEnter(Player& player)
{
	player.SetIsGrounded(true);
	jumpTime = 0;
}

void JumpState::HandleInput(Player& player)
{
	jumpTime++;
	if(player.GetVelocity().y == 0)
	{
		Vector2f currentVel = player.GetVelocity();
		Vector2f vel = { (currentVel.x),(currentVel.y - 2) };
		player.SetVelocity(vel);
	}

	if (Play::KeyDown(VK_LEFT))
	{
		if (player.GetAcceleration().x >= 0)
		{
			const Vector2f& currentAcc = player.GetAcceleration();
			const Vector2f& acc = { -MOVEACC/2, (currentAcc.y) };
			player.SetIsLeftFacing(true);
			player.SetAcceleration(acc);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		if (player.GetAcceleration().x <= 0)
		{
			const Vector2f& currentAcc = player.GetAcceleration();
			const Vector2f& acc = { MOVEACC/2, (currentAcc.y) };
			player.SetIsLeftFacing(false);
			player.SetAcceleration(acc);
		}
	}
	else
	{
		//float acc = -(player.GetAcceleration().x);
		player.SetAcceleration({ 0.0f, player.GetAcceleration().y });
	}


	// When the player is no longer holding space and the height he is is above his initial position,
	// Change to fall state
	if ((!(Play::KeyDown(VK_SPACE)) || jumpTime > jumpDuration))
	{
		player.SwapPlayerState(FallState::getInstance());
	}

}

void JumpState::DrawPlayer(const Player& player, GameState& state) const
{
	float correctedX = player.GetPosition().x - state.camera.pos.x;
	float correctedY = player.GetPosition().y - state.camera.pos.y;

	if (!(player.GetIsLeftFacing()))
	{
		Play::DrawSprite(zoolJumpRpng, { correctedX, correctedY }, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
	}

	if (player.GetIsLeftFacing())
	{
		Play::DrawSprite(zoolJumpLpng, { correctedX, correctedY }, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
	}
}

void JumpState::StateExit(Player& player)
{

}

// FallState
PlayerState& FallState::getInstance()
{
	static FallState singleton;
	return singleton;
}

void FallState::StateEnter(Player& player)
{
	player.SetIsGrounded(false);
}

void FallState::HandleInput(Player& player)
{
	Vector2f currentAcc = player.GetAcceleration();
	Vector2f acc = { (currentAcc.x),(GRAVITY) };
	player.SetAcceleration(acc);
	
	if (Play::KeyDown(VK_LEFT))
	{
		if (player.GetAcceleration().x >= 0)
		{
			const Vector2f& acc = { -MOVEACC/2, (currentAcc.y) };
			player.SetIsLeftFacing(true);
			player.SetAcceleration(acc);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		if (player.GetAcceleration().x <= 0)
		{
			const Vector2f& acc = { MOVEACC/2, (currentAcc.y) };
			player.SetIsLeftFacing(false);
			player.SetAcceleration(acc);
		}
	}
	else
	{
		player.SetAcceleration({ 0.0f, player.GetAcceleration().y });
	}

	if (player.GetIsGrounded())
	{
		player.SwapPlayerState(IdleState::getInstance());
	}
}

void FallState::DrawPlayer(const Player& player, GameState& state) const
{
	float correctedX = player.GetPosition().x - state.camera.pos.x;
	float correctedY = player.GetPosition().y - state.camera.pos.y;

	if (!(player.GetIsLeftFacing()))
	{
		Play::DrawSprite(zoolFallRpng, { correctedX, correctedY }, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
	}

	if (player.GetIsLeftFacing())
	{
		Play::DrawSprite(zoolFallLpng, { correctedX, correctedY }, static_cast<int>(SINGLE_FRAME_ANIM_SPEED * state.time));
	}
}

void FallState::StateExit(Player& player)
{
	player.SetVelocity({ player.GetVelocity().x, (0.0f) });
}
