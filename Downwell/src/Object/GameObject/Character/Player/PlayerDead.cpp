#include "PlayerDead.h"
#include "Player.h"

void PlayerDead::Enter(Player& player)
{
	player.SetDirectionX();
	player.SetVelocity({ player.GetVelocity().x, 0.0f });
}

void PlayerDead::Update(Player& player)
{
	player.SetColor(WHITE);

	player.DeadDrag();
}

void PlayerDead::Exit(Player& player)
{
}
