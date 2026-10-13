#include "PlayerMove.h"
#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "PlayerFall.h"
#include "Player.h"
#include "Input.h"

void PlayerMove::Enter(Player& player)
{
	(void)player;
}

void PlayerMove::Update(Player& player)
{
	player.SetColor(RED);

	//ˆÚ“®
	bool isMove = (Input::IsPress(Action::Left)) ^ (Input::IsPress(Action::Right));
	if (!isMove)
	{
		player.RequestState(std::make_unique<PlayerIdle>());
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
		player.RequestState(std::make_unique<PlayerJump>());
	}

	//—Ž‰º
	if (!player.IsGround())
	{
		player.RequestState(std::make_unique<PlayerFall>());
	}
}

void PlayerMove::Exit(Player& player)
{
	(void)player;
}
