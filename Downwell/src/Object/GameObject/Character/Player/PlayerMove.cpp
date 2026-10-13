#include "PlayerMove.h"
#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "PlayerFall.h"
#include "Player.h"
#include "DxLib.h"

void PlayerMove::Enter(Player& player)
{
	(void)player;
}

void PlayerMove::Update(Player& player)
{
	player.SetColor(RED);

	//ˆÚ“®
	bool isMove = ((CheckHitKey(KEY_INPUT_A)) ^ (CheckHitKey(KEY_INPUT_D)));
	if (!isMove)
	{
		player.RequestState(std::make_unique<PlayerIdle>());
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		player.SetDirectionX(-1.0f);
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		player.SetDirectionX(1.0f);
	}

	//ƒWƒƒƒ“ƒv
	if (player.GetJumpTrigger())
	{
		player.RequestState(std::make_unique<PlayerJump>());
	}

	//—Ž‰º
	if (!player.IsGround())
	{
		player.RequestState(std::make_unique<PlayerFall>());
	}
}

void PlayerMove::Exit(Player& player)
{
	(void)player;
}
