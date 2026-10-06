#include "PlayerMove.h"
#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "Player.h"
#include "Main.h"

void PlayerMove::Enter(Player& player)
{
}

void PlayerMove::Update(Player& player)
{
	player.m_R = 255;
	player.m_G = 0;
	player.m_B = 0;

	//ˆÚ“®
	if (CheckHitKey(KEY_INPUT_A)) player.SetAccel({ -50000.0f, 0.0f });
	if (CheckHitKey(KEY_INPUT_D)) player.SetAccel({ 50000.0f, 0.0f });


	if (player.GetVelocity().IsNearlyZero(1.0f))
	{
		player.SetState(std::make_unique<PlayerIdle>());
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && player.IsGround())
	{
		player.SetState(std::make_unique<PlayerJump>());
	}
}

void PlayerMove::Exit(Player& player)
{
}
