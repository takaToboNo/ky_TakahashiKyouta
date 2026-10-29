#include "PlayerJump.h"
#include "PlayerMove.h"
#include "PlayerShot.h"
#include "PlayerFall.h"
#include "PlayerDead.h"
#include "Player.h"
#include "Input.h"

#include "AudioManager.h"

void PlayerJump::Enter(Player& player)
{
	AudioManager::GetInstance().PlaySE("Jump");

	//ジャンプ
	player.Jump();

	player.SetCanAutoShot(false);
}

void PlayerJump::Update(Player& player)
{
	player.SetColor(PLAYER_JUMP_COLOR);

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

	//落下
	if (player.GetVelocity().y >= 0.0f)
	{
		player.RequestState(EPlayerState::Fall);
	}

	//死亡
	if (player.IsDead())
	{
		player.RequestState(EPlayerState::Dead);
	}
	
}

void PlayerJump::Exit(Player& player)
{
}
