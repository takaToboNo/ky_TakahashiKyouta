#include "PlayerJump.h"
#include "PlayerMove.h"
#include "Player.h"
#include "Main.h"

void PlayerJump::Enter(Player& player)
{
	player.Jump();
}

void PlayerJump::Update(Player& player)
{
	player.m_R = 0;
	player.m_G = 0;
	player.m_B = 255;

	//ˆÚ“®
	if (CheckHitKey(KEY_INPUT_A)) player.SetAccel({ -50000.0f, 0.0f });
	if (CheckHitKey(KEY_INPUT_D)) player.SetAccel({ 50000.0f, 0.0f });

	if (player.IsGround())
	{
		player.SetState(std::make_unique<PlayerMove>());
	}
}

void PlayerJump::Exit(Player& player)
{
	player.SetGround(true);
}
