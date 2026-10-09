#include "PlayerJump.h"
#include "PlayerMove.h"
#include "PlayerShot.h"
#include "PlayerFall.h"
#include "Player.h"
#include "DxLib.h"

void PlayerJump::Enter(Player& player)
{
	//ジャンプ
	player.Jump();

	player.SetCanAutoShot(false);
}

void PlayerJump::Update(Player& player)
{
	player.SetColor(BLUE);

	//抵抗
	player.AirDrag();

	//移動
	bool isMove = ((CheckHitKey(KEY_INPUT_A)) ^ (CheckHitKey(KEY_INPUT_D)));
	if (!isMove)
	{
		player.SetDirectionX();
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		player.SetDirectionX(-1.0f);
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		player.SetDirectionX(1.0f);
	}

	//ショット
	if (player.GetJumpTrigger())
	{
		player.RequestState(std::make_unique<PlayerShot>());
	}

	//落下
	if (player.GetVelocity().y >= 0.0f)
	{
		player.RequestState(std::make_unique<PlayerFall>());
	}
	
}

void PlayerJump::Exit(Player& player)
{
}
