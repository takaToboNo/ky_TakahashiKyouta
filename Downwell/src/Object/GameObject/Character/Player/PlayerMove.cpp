#include "PlayerMove.h"
#include "Player.h"
#include "Input.h"

void PlayerMove::Enter(Player& player)
{
	(void)player;
}

void PlayerMove::Update(Player& player)
{
	player.SetColor(PLAYER_MOVE_COLOR);

	//移動
	bool isMove = (Input::IsPress(Action::Left)) ^ (Input::IsPress(Action::Right));
	if (!isMove)
	{
		player.RequestState(EPlayerState::Idle);
	}
	else if (Input::IsPress(Action::Left))
	{
		player.SetDirectionX(-1.0f);
	}
	else if (Input::IsPress(Action::Right))
	{
		player.SetDirectionX(1.0f);
	}

	//ジャンプ
	if (Input::IsTrigger(Action::Action))
	{
		player.RequestState(EPlayerState::Jump);
	}

	//落下
	if (!player.IsGround())
	{
		player.RequestState(EPlayerState::Fall);
	}

	//死亡
	if (player.IsDead())
	{
		player.RequestState(EPlayerState::Dead);
	}
}

void PlayerMove::Exit(Player& player)
{
	(void)player;
}
