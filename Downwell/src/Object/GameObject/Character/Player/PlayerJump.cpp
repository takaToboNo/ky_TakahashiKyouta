#include "PlayerJump.h"
#include "PlayerMove.h"
#include "PlayerShot.h"
#include "PlayerFall.h"
#include "PlayerDead.h"
#include "Player.h"
#include "Input.h"

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
	bool isMove = (Input::IsPress(Action::Left)) ^ (Input::IsPress(Action::Right));
	if (!isMove)
	{
		player.SetDirectionX();
	}
	else if (Input::IsPress(Action::Left))
	{
		player.SetDirectionX(-1.0f);
	}
	else if (Input::IsPress(Action::Right))
	{
		player.SetDirectionX(1.0f);
	}

	//ショット
	if (Input::IsTrigger(Action::Action))
	{
		player.RequestState(std::make_unique<PlayerShot>());
	}

	//落下
	if (player.GetVelocity().y >= 0.0f)
	{
		player.RequestState(std::make_unique<PlayerFall>());
	}

	//死亡
	if (player.IsDead())
	{
		player.RequestState(std::make_unique<PlayerDead>());
	}
	
}

void PlayerJump::Exit(Player& player)
{
}
