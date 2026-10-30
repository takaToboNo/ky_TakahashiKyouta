#pragma once
#include "WalkerEnemyState.h"

class WalkerEnemy;

class WalkerEnemyMove : public IWalkerEnemyState
{
public:
	void Enter(WalkerEnemy& walkerEnemy) override;
	void Update(WalkerEnemy& walkerEnemy) override;
	void Exit(WalkerEnemy& walkerEnemy) override;
	const char* GetStateName() const { return "Move"; }
};
