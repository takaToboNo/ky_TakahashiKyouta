#include "PlayerShot.h"
#include "PlayerFall.h"
#include "Player.h"
#include "DxLib.h"

void PlayerShot::Enter(Player& player)
{
	
}

void PlayerShot::Update(Player& player)
{
	player.SetColor(PURPLE);

	player.RequestState(std::make_unique<PlayerFall>());
}

void PlayerShot::Exit(Player& player)
{
}
