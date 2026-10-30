#include "PlayerShot.h"
#include "PlayerFall.h"
#include "Player.h"

void PlayerShot::Enter(Player& player)
{
}

void PlayerShot::Update(Player& player)
{
	player.SetColor(PLAYER_SHOT_COLOR);

	player.Shot(player.GetPosition());

	player.RequestState(EPlayerState::Fall);
}

void PlayerShot::Exit(Player& player)
{
}
