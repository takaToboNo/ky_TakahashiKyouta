#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerJump.h"
#include "PlayerFall.h"
#include "Player.h"
#include "DxLib.h"

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
	bool isMove = ((CheckHitKey(KEY_INPUT_A)) ^ (CheckHitKey(KEY_INPUT_D)));
	if (isMove)
	{
		player.RequestState(std::make_unique<PlayerMove>());
	}

	//ƒWƒƒƒ“ƒv
	if (player.GetJumpTrigger())
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
