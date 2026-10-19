#pragma once
#include "PlayerState.h"

class Player;

class PlayerDead : public IPlayerState
{
private:

public:
	void Enter(Player& player) override;
	void Update(Player& player) override;
	void Exit(Player& player) override;
	const char* GetStateName() const { return "Dead"; }
};
