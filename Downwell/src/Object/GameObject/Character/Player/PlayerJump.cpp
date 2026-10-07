#include "PlayerJump.h"
#include "PlayerMove.h"
#include "Player.h"
#include "Main.h"

void PlayerJump::Enter(Player& player)
{
	//ジャンプ
	player.Jump();
}

void PlayerJump::Update(Player& player)
{
	player.SetColor(kBlue);

	//抵抗
	player.AirDrag();

	//移動
	if (CheckHitKey(KEY_INPUT_A)) player.MoveLeftRight(-1.0f);
	if (CheckHitKey(KEY_INPUT_D)) player.MoveLeftRight(1.0f);

	//着地
	if (player.IsGround())
	{
		player.RequestState(std::make_unique<PlayerMove>());
	}
}

void PlayerJump::Exit(Player& player)
{
	//着地
	player.SetGround(true);
}
