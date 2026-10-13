#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerJump.h"
#include "PlayerFall.h"
#include "Player.h"
#include "Input.h"

void PlayerIdle::Enter(Player& player)
{
	//’âŽ~
	player.SetVelocity(Vector2::Zero());
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

	//—Ž‰º
	if (!player.IsGround())
	{
		player.RequestState(std::make_unique<PlayerFall>());
	}
}

void PlayerIdle::Exit(Player& player)
{
	(void)player;
}
