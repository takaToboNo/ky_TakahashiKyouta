#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerJump.h"
#include "PlayerFall.h"
#include "PlayerDead.h"
#include "Player.h"
#include "Input.h"

void PlayerIdle::Enter(Player& player)
{
	//’â~
	player.SetVelocity({ 0.0f,player.GetVelocity().y });
	player.SetDirectionX();
}

void PlayerIdle::Update(Player& player)
{
	player.SetColor(PLAYER_IDLE_COLOR);

	//ˆÚ“®
	bool isMove = (Input::IsPress(Action::Left)) ^ (Input::IsPress(Action::Right));
	if (isMove)
	{
		player.RequestState(EPlayerState::Move);
	}

	//ƒWƒƒƒ“ƒv
	if (Input::IsTrigger(Action::Action))
	{
		player.RequestState(EPlayerState::Jump);
	}

	//—‰º
	if (!player.IsGround())
	{
		player.RequestState(EPlayerState::Fall);
	}

	//’ïR
	player.GroundDrag();

	//€–S
	if (player.IsDead())
	{
		player.RequestState(EPlayerState::Dead);
	}
}

void PlayerIdle::Exit(Player& player)
{
	(void)player;
}
