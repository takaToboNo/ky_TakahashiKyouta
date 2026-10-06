#pragma once
#include "PlayerState.h"

class Player;

class PlayerIdle : public IPlayerState
{
public:
	void Enter(Player& player) override;
	void Update(Player& player) override;
	void Exit(Player& player) override;
};
