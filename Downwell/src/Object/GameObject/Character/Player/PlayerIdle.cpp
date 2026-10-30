#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerJump.h"
#include "PlayerFall.h"
#include "PlayerDead.h"
#include "Player.h"
#include "Input.h"

void PlayerIdle::Enter(Player& player)
{
	//停止
	player.SetVelocity({ 0.0f,player.GetVelocity().y });
	player.SetDirectionX();
}

void PlayerIdle::Update(Player& player)
{
	player.SetColor(PLAYER_IDLE_COLOR);

	//移動
	bool isMove = (Input::IsPress(Action::Left)) ^ (Input::IsPress(Action::Right));
	if (isMove)
	{
		player.RequestState(EPlayerState::Move);
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

	//抵抗
	player.GroundDrag();

	//死亡
	if (player.IsDead())
	{
		player.RequestState(EPlayerState::Dead);
	}
}

void PlayerIdle::Exit(Player& player)
{
	(void)player;
}
