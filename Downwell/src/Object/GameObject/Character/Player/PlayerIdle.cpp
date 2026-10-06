#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerJump.h"
#include "Player.h"
#include "Main.h"

void PlayerIdle::Enter(Player& player)
{
}

void PlayerIdle::Update(Player& player)
{
	player.m_R = 0;
	player.m_G = 255;
	player.m_B = 0;

	if (CheckHitKey(KEY_INPUT_SPACE) && player.IsGround())
	{
		player.SetState(std::make_unique<PlayerJump>());
	}

	if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D))
	{
		player.SetState(std::make_unique<PlayerMove>());
	}
}

void PlayerIdle::Exit(Player& player)
{
}
