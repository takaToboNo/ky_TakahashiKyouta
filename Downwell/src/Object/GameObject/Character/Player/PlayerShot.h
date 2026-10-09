#pragma once
#include "PlayerState.h"

class Player;

class PlayerShot : public IPlayerState
{
public:
	void Enter(Player& player) override;
	void Update(Player& player) override;
	void Exit(Player& player) override;
	const char* GetStateName() const { return "Shot"; }
};
