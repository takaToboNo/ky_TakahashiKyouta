#include "PlayerFall.h"
#include "PlayerMove.h"
#include "PlayerShot.h"
#include "Player.h"
#include "Input.h"

void PlayerFall::Enter(Player& player)
{
}

void PlayerFall::Update(Player& player)
{
	player.SetColor(YELLOW);

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

	//自動ショット
	m_ShotInterval--;
	if (Input::IsPress(Action::Action) && m_ShotInterval < 0 && player.GetCanAutoShot())
	{
		player.RequestState(std::make_unique<PlayerShot>());
	}

	//着地
	if (player.IsGround())
	{
		player.RequestState(std::make_unique<PlayerMove>());
		player.Reload();
	}
}

void PlayerFall::Exit(Player& player)
{
}
