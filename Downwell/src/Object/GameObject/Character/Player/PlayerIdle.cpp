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
	player.SetColor(GREEN);

	//ˆÚ“®
	bool isMove = (Input::IsPress(Action::Left)) ^ (Input::IsPress(Action::Right));
	if (isMove)
	{
		player.RequestState(std::make_unique<PlayerMove>());
	}

	//ƒWƒƒƒ“ƒv
	if (Input::IsTrigger(Action::Action))
	{
		player.RequestState(std::make_unique<PlayerJump>());
	}

	//—‰º
	if (!player.IsGround())
	{
		player.RequestState(std::make_unique<PlayerFall>());
	}

	//’ïR
	player.GroundDrag();

	//€–S
	if (player.IsDead())
	{
		player.RequestState(std::make_unique<PlayerDead>());
	}
}

void PlayerIdle::Exit(Player& player)
{
	(void)player;
}
