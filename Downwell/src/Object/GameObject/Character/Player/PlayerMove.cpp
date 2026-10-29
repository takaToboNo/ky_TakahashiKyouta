#include "PlayerMove.h"
#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "PlayerFall.h"
#include "PlayerDead.h"
#include "Player.h"
#include "Input.h"

void PlayerMove::Enter(Player& player)
{
	(void)player;
}

void PlayerMove::Update(Player& player)
{
	player.SetColor(PLAYER_MOVE_COLOR);

	//ˆÚ“®
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

	//ƒWƒƒƒ“ƒv
	if (Input::IsTrigger(Action::Action))
	{
		player.RequestState(EPlayerState::Jump);
	}

	//—Ž‰º
	if (!player.IsGround())
	{
		player.RequestState(EPlayerState::Fall);
	}

	//Ž€–S
	if (player.IsDead())
	{
		player.RequestState(EPlayerState::Dead);
	}
}

void PlayerMove::Exit(Player& player)
{
	(void)player;
}
