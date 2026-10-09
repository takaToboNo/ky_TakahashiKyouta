#include "PlayerMove.h"
#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "Player.h"
#include "DxLib.h"

void PlayerMove::Enter(Player& player)
{
	(void)player;
}

void PlayerMove::Update(Player& player)
{
	player.SetColor(RED);

	//移動
	if (CheckHitKey(KEY_INPUT_A))
	{
		player.SetDirectionX(-1.0f);
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		player.SetDirectionX(1.0f);
	}
	else
	{	//ADキーどちらも押していない
		player.RequestState(std::make_unique<PlayerIdle>());
	}

	//ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) && player.IsGround() && player.GetJumpTrigger())
	{
		player.RequestState(std::make_unique<PlayerJump>());
	}
}

void PlayerMove::Exit(Player& player)
{
	(void)player;
}
