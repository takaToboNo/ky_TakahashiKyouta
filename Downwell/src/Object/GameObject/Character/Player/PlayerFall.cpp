#include "PlayerFall.h"
#include "PlayerMove.h"
#include "PlayerShot.h"
#include "PlayerDead.h"
#include "Player.h"
#include "Input.h"

#include "AudioManager.h"

void PlayerFall::Enter(Player& player)
{
	m_ShotInterval = SHOT_INTERVAL;
}

void PlayerFall::Update(Player& player)
{
	player.SetColor(PLAYER_FALL_COLOR);

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
		player.RequestState(EPlayerState::Shot);
	}

	//自動ショット
	m_ShotInterval--;
	if (Input::IsPress(Action::Action) && m_ShotInterval < 0 && player.GetCanAutoShot())
	{
		player.RequestState(EPlayerState::Shot);
	}

	//着地
	if (player.IsGround())
	{
		AudioManager::GetInstance().PlaySE("Land");

		player.RequestState(EPlayerState::Move);
		player.Reload();
	}

	//死亡
	if (player.IsDead())
	{
		player.RequestState(EPlayerState::Dead);
	}
}

void PlayerFall::Exit(Player& player)
{
}
