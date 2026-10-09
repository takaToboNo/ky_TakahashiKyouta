#include "PlayerFall.h"
#include "PlayerMove.h"
#include "PlayerShot.h"
#include "Player.h"
#include "DxLib.h"

void PlayerFall::Enter(Player& player)
{
}

void PlayerFall::Update(Player& player)
{
	player.SetColor(YELLOW);

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

	//自動ショット
	m_ShotInterval--;
	if (CheckHitKey(KEY_INPUT_SPACE) && m_ShotInterval < 0 && player.GetCanAutoShot())
	{
		player.RequestState(std::make_unique<PlayerShot>());
	}

	//着地
	if (player.IsGround())
	{
		player.RequestState(std::make_unique<PlayerMove>());
	}
}

void PlayerFall::Exit(Player& player)
{
	player.SetVelocity({ player.GetVelocity().x, 0.0f });
}
