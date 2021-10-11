#include "PlayerStatesConcrete.h"

void IdleState::HandleInput(Player* player)
{
	if (Play::KeyDown(VK_LEFT) || Play::KeyDown(VK_RIGHT))
	{
		player->SetPlayerState(WalkState::getInstance());
	}
}

void IdleState::DrawPlayer(const Player* player, GameState& state) const
{
	if (!(player->GetIsLeftFacing()))
	{
		Play::DrawSprite(Play::GetSpriteId("playerIdle_right"), player->GetPosition(), static_cast<int>(10 * state.time));
	}
	else if (player->GetIsLeftFacing())
	{
		Play::DrawSprite(Play::GetSpriteId("playerIdle_left"), player->GetPosition(), static_cast<int>(10 * state.time));
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
	// Allow the player to move the alien along the horizontal axis using the directional keys
	if (Play::KeyDown(VK_LEFT) && player->GetPosition().x > S_HALF_LIMIT)
	{
		Point2f currentPos = player->GetPosition();
		Point2f pos = { (currentPos.x - 1),(currentPos.y) };
		player->SetPosition(pos);
		player->SetIsLeftFacing(true);
	}

	if (Play::KeyDown(VK_RIGHT) && (player->GetPosition().x + S_HALF_LIMIT) < S_DISPLAY_WIDTH)
	{
		Point2f currentPos = player->GetPosition();
		Point2f pos = { (currentPos.x + 1),(currentPos.y) };
		player->SetPosition(pos);
		player->SetIsLeftFacing(false);
	}

	if (!Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_LEFT))
	{
		player->SetPlayerState(IdleState::getInstance());
	}
}

void WalkState::DrawPlayer(const Player* player, GameState& state) const
{
	if (!(player->GetIsLeftFacing()))
	{
		Play::DrawSprite(Play::GetSpriteId("playerWalk_right_4"), player->GetPosition(), static_cast<int>(8 * state.time));
	}
	else if (player->GetIsLeftFacing())
	{
		Play::DrawSprite(Play::GetSpriteId("playerWalk_left_4"), player->GetPosition(), static_cast<int>(8 * state.time));
	}
}

PlayerState& WalkState::getInstance()
{
	static WalkState singleton;
	return singleton;
}