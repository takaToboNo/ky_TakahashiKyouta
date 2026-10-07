#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerJump.h"
#include "Player.h"
#include "DxLib.h"

void PlayerIdle::Enter(Player& player)
{
	//’âŽ~
	player.SetVelocity(Vector2::Zero());
}

void PlayerIdle::Update(Player& player)
{
	player.SetColor(kGreen);

	//ˆÚ“®
	if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_D))
	{
		player.RequestState(std::make_unique<PlayerMove>());
	}

	//ƒWƒƒƒ“ƒv
	if (CheckHitKey(KEY_INPUT_SPACE) && player.IsGround())
	{
		player.RequestState(std::make_unique<PlayerJump>());
	}
}

void PlayerIdle::Exit(Player& player)
{
}
