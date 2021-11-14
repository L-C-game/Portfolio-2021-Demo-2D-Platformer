/*
	Author: Laura Mary Clarke 2020
	GitHub: L-C-game

	Definitions of the playerstate concrete methods.
*/

#include "PlayerStatesConcrete.h"
#include "GameObject.h"


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
		player.SetPlayerState(WalkState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player.SetPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE) && (player.GetIsGrounded()))
	{
		player.SetPlayerState(JumpState::getInstance());
	}

	if (!player.GetIsGrounded())
	{
		player.SetPlayerState(FallState::getInstance());
	}

	if (player.GetIsHurt())
	{
		player.SetPlayerState(HurtState::getInstance());
	}
}

void IdleState::SetupAnim(Player& player)
{
	player.SetAnimSpeed(g_SINGLE_FRAME_ANIM_SPEED);

	if (!(player.GetIsLeftFacing()))
	{
		player.SetPlayerID(zoolIdleRpng);
	}

	if (player.GetIsLeftFacing())
	{
		player.SetPlayerID(zoolIdleLpng);
	}
}

void IdleState::DrawPlayer(const Player& player, GameState& gameState) const
{
	Play::DrawSprite(player.GetPlayerID(), player.GetPosition() - gameState.camera.pos, static_cast<int>(player.GetAnimSpeed() * gameState.time));
}

void IdleState::StateExit(Player& player)
{
	player;
}

// WalkState
PlayerState& WalkState::getInstance()
{
	static WalkState singleton;
	return singleton;
}

void WalkState::StateEnter(Player& player)
{
	player;
}

void WalkState::HandleInput(Player& player)
{
	// Input handling
	if (Play::KeyDown(VK_LEFT))
	{
		if (player.GetAcceleration().x >= 0)
		{
			const Vector2f& currentAcc = player.GetAcceleration();
			const Vector2f& acc = { -g_MOVE_ACC, (currentAcc.y) };
			player.SetIsLeftFacing(true);
			player.SetAcceleration(acc);
		}
	}

	if (Play::KeyDown(VK_RIGHT))
	{
		if (player.GetAcceleration().x <= 0)
		{
			const Vector2f& currentAcc = player.GetAcceleration();
			const Vector2f& acc = { g_MOVE_ACC, (currentAcc.y) };
			player.SetIsLeftFacing(false);
			player.SetAcceleration(acc);
		}
	}

	if ((!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)) || (Play::KeyDown(VK_LEFT) && Play::KeyDown(VK_RIGHT)))
	{
		player.SetPlayerState(SkidState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player.SetPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE) && (player.GetIsGrounded()))
	{
		player.SetPlayerState(JumpState::getInstance());
	}

	if (!player.GetIsGrounded())
	{
		player.SetPlayerState(FallState::getInstance());
	}

	if (player.GetIsHurt())
	{
		player.SetPlayerState(HurtState::getInstance());
	}
}

void WalkState::SetupAnim(Player& player)
{
	player.SetAnimSpeed(g_RUN_ANIM_SPEED);

	if (!(player.GetIsLeftFacing()))
	{
		player.SetPlayerID(zoolWalkRpng);
	}

	if (player.GetIsLeftFacing())
	{
		player.SetPlayerID(zoolWalkLpng);
	}
}

void WalkState::DrawPlayer(const Player& player, GameState& gameState) const
{
	Play::DrawSprite(player.GetPlayerID(), player.GetPosition() - gameState.camera.pos, static_cast<int>(player.GetAnimSpeed() * gameState.time));
}

void WalkState::StateExit(Player& player)
{
	player;
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
		player.SetPlayerState(WalkState::getInstance());
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		player.SetIsLeftFacing(false);
		player.SetPlayerState(WalkState::getInstance());
	}

	if ((abs(player.GetVelocity().x) <= g_MINIMUM_SPEED_RUN) && (!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)) || (Play::KeyDown(VK_LEFT) && Play::KeyDown(VK_RIGHT)))
	{
		// If the player presses neither of L and R set to idle state
		player.SetPlayerState(IdleState::getInstance());
	}

	if (Play::KeyDown(VK_DOWN))
	{
		player.SetPlayerState(CrouchState::getInstance());
	}

	if (Play::KeyDown(VK_SPACE) && (player.GetIsGrounded()))
	{
		player.SetPlayerState(JumpState::getInstance());
	}

	if (!player.GetIsGrounded() && player.GetVelocity().y <= 0.0f)
	{
		player.SetPlayerState(FallState::getInstance());
	}

	if (player.GetIsHurt())
	{
		player.SetPlayerState(HurtState::getInstance());
	}
}

void SkidState::SetupAnim(Player& player)
{
	player.SetAnimSpeed(g_SINGLE_FRAME_ANIM_SPEED);

	if (!(player.GetIsLeftFacing()))
	{
		player.SetPlayerID(zoolSkidRpng);
	}

	if (player.GetIsLeftFacing())
	{
		player.SetPlayerID(zoolSkidLpng);
	}
}

void SkidState::DrawPlayer(const Player& player, GameState& gameState) const
{
	Play::DrawSprite(player.GetPlayerID(), player.GetPosition() - gameState.camera.pos, static_cast<int>(player.GetAnimSpeed() * gameState.time));
}

void SkidState::StateExit(Player& player)
{
	player;
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
		player.SetPlayerState(WalkState::getInstance());
	}
	else if (!(Play::KeyDown(VK_DOWN)) && (!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT)))
	{
		player.SetPlayerState(IdleState::getInstance());
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

	if (player.GetIsHurt())
	{
		player.SetPlayerState(HurtState::getInstance());
	}
}

void CrouchState::SetupAnim(Player& player)
{
	player.SetAnimSpeed(g_SINGLE_FRAME_ANIM_SPEED);

	if (!(player.GetIsLeftFacing()))
	{
		player.SetPlayerID(zoolCrouchRpng);
	}

	if (player.GetIsLeftFacing())
	{
		player.SetPlayerID(zoolCrouchLpng);
	}
}

void CrouchState::DrawPlayer(const Player& player, GameState& gameState) const
{
	Play::DrawSprite(player.GetPlayerID(), player.GetPosition() - gameState.camera.pos, static_cast<int>(player.GetAnimSpeed() * gameState.time));
}

void CrouchState::StateExit(Player& player)
{
	player;
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
	player.SetJumpTimer(0);
	Play::PlayAudio("jump");
}

void JumpState::HandleInput(Player& player)
{
	player.SetJumpTimer(player.GetJumpTimer() + 1);

	if(player.GetVelocity().y == 0)
	{
		Vector2f currentVel = player.GetVelocity();
		Vector2f vel = { (currentVel.x),(currentVel.y - g_JUMP_SPEED) };
		player.SetVelocity(vel);
	}

	if (Play::KeyDown(VK_LEFT))
	{
		if (player.GetAcceleration().x >= 0)
		{
			const Vector2f& currentAcc = player.GetAcceleration();
			const Vector2f& acc = { -g_MOVE_ACC, (currentAcc.y) };
			player.SetIsLeftFacing(true);
			player.SetAcceleration(acc);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		if (player.GetAcceleration().x <= 0)
		{
			const Vector2f& currentAcc = player.GetAcceleration();
			const Vector2f& acc = { g_MOVE_ACC, (currentAcc.y) };
			player.SetIsLeftFacing(false);
			player.SetAcceleration(acc);
		}
	}
	else
	{
		player.SetAcceleration({ 0.0f, player.GetAcceleration().y });
	}

	// When the player is no longer holding space and the height he is is above his initial position,
	// Change to fall state
	if ((!(Play::KeyDown(VK_SPACE)) || player.GetJumpTimer() > g_JUMP_DURATION))
	{
		player.SetPlayerState(FallState::getInstance());
	}

	if (player.GetIsHurt())
	{
		player.SetPlayerState(HurtState::getInstance());
	}
}

void JumpState::SetupAnim(Player& player)
{
	player.SetAnimSpeed(g_SINGLE_FRAME_ANIM_SPEED);

	if (!(player.GetIsLeftFacing()))
	{
		player.SetPlayerID(zoolJumpRpng);
	}

	if (player.GetIsLeftFacing())
	{
		player.SetPlayerID(zoolJumpLpng);
	}
}

void JumpState::DrawPlayer(const Player& player, GameState& gameState) const
{
	Play::DrawSprite(player.GetPlayerID(), player.GetPosition() - gameState.camera.pos, static_cast<int>(player.GetAnimSpeed() * gameState.time));
}

void JumpState::StateExit(Player& player)
{
	player;
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
	Vector2f acc = { (currentAcc.x),(g_GRAVITY) };
	player.SetAcceleration(acc);
	
	if (Play::KeyDown(VK_LEFT))
	{
		if (player.GetAcceleration().x >= 0)
		{
			const Vector2f& accel = { -g_MOVE_ACC, (currentAcc.y) };
			player.SetIsLeftFacing(true);
			player.SetAcceleration(accel);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		if (player.GetAcceleration().x <= 0)
		{
			const Vector2f& accel = { g_MOVE_ACC, (currentAcc.y) };
			player.SetIsLeftFacing(false);
			player.SetAcceleration(accel);
		}
	}
	else
	{
		player.SetAcceleration({ 0.0f, player.GetAcceleration().y });
	}

	if (player.GetIsGrounded())
	{
		player.SetPlayerState(IdleState::getInstance());
	}

	if (player.GetIsHurt())
	{
		player.SetPlayerState(HurtState::getInstance());
	}
}

void FallState::SetupAnim(Player& player)
{
	player.SetAnimSpeed(g_SINGLE_FRAME_ANIM_SPEED);

	if (!(player.GetIsLeftFacing()))
	{
		player.SetPlayerID(zoolFallRpng);
	}

	if (player.GetIsLeftFacing())
	{
		player.SetPlayerID(zoolFallLpng);
	}
}

void FallState::DrawPlayer(const Player& player, GameState& gameState) const
{
	Play::DrawSprite(player.GetPlayerID(), player.GetPosition() - gameState.camera.pos, static_cast<int>(player.GetAnimSpeed() * gameState.time));
}

void FallState::StateExit(Player& player)
{
	player.SetVelocity({ player.GetVelocity().x, (0.0f) });
	player.SetIsGrounded(true);
}

// Controls access to the singleton instance, 
PlayerState& HurtState::getInstance()
{
	static HurtState singleton;
	return singleton;
}

void HurtState::StateEnter(Player& player)
{
	player.SetiFramesTimer(0);
	player.SetBlinkTimer(0);
	player.SetIsGrounded(true);
	player.SetAcceleration({ 0.0f, player.GetAcceleration().y });
}

void HurtState::HandleInput(Player& player)
{
	player.SetiFramesTimer(player.GetiFramesTimer() + 1);
	player.SetBlinkTimer(player.GetBlinkTimer() + 1);

	if (player.GetAcceleration().x <= 0 && player.GetiFramesTimer() < g_I_FRAMES_DURATION)
	{
		if (!player.GetIsLeftFacing())
		{
			const Vector2f& acc = { -g_STUN_ACC * 2, -g_STUN_ACC * g_TENTH };
			player.SetAcceleration(acc);
			player.SetIsLeftFacing(false);
		}

		if (player.GetIsLeftFacing())
		{
			const Vector2f& acc = { g_STUN_ACC * 2, -g_STUN_ACC * g_TENTH };
			player.SetAcceleration(acc);
			player.SetIsLeftFacing(true);
		}
	}

	if (player.GetiFramesTimer() >= g_I_FRAMES_DURATION)
	{
		player.SetPlayerState(IdleState::getInstance());
	}

	if (!player.GetIsBlinking() && player.GetBlinkTimer() >= g_BLINK_DURATION)
	{
		player.SetIsBlinking(true);
		player.SetBlinkTimer(0);
	}

	if (player.GetIsBlinking() && player.GetBlinkTimer() >= g_BLINK_DURATION)
	{
		player.SetIsBlinking(false);
		player.SetBlinkTimer(0);
	}
}

void HurtState::StateExit(Player& player)
{
	player.SetIsHurt(false);
	player.SetAcceleration({ 0.0f, 0.0f });
}

void HurtState::SetupAnim(Player& player)
{
	player.SetAnimSpeed(g_SINGLE_FRAME_ANIM_SPEED);

	if (!(player.GetIsLeftFacing()))
	{
		player.SetPlayerID(zoolJumpRpng);
	}

	if (player.GetIsLeftFacing())
	{
		player.SetPlayerID(zoolJumpLpng);
	}
}

void HurtState::DrawPlayer(const Player& player, GameState& gameState) const
{
	if (!player.GetIsBlinking())
	{
		Play::DrawSprite(player.GetPlayerID(), player.GetPosition() - gameState.camera.pos, static_cast<int>(player.GetAnimSpeed() * gameState.time));
	}
	
	if (player.GetIsBlinking())
	{
		Play::DrawSpriteTransparent(Play::GetSpriteName(player.GetPlayerID()), player.GetPosition() - gameState.camera.pos, static_cast<int>(player.GetAnimSpeed() * gameState.time), 0.0f);
	}
}

