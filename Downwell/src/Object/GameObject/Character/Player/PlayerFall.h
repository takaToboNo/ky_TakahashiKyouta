#pragma once
#include "PlayerState.h"

class Player;

class PlayerFall : public IPlayerState
{
private:
	static constexpr int SHOT_INTERVAL = 6;
	int m_ShotInterval = SHOT_INTERVAL;//‰¼

public:
	void Enter(Player& player) override;
	void Update(Player& player) override;
	void Exit(Player& player) override;
	const char* GetStateName() const { return "Fall"; }
};
