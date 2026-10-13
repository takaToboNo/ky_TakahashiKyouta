#pragma once
#include "PlayerState.h"

class Player;

class PlayerFall : public IPlayerState
{
private:
	int m_ShotInterval = 6;//‰¼

public:
	void Enter(Player& player) override;
	void Update(Player& player) override;
	void Exit(Player& player) override;
	const char* GetStateName() const { return "Fall"; }
};
