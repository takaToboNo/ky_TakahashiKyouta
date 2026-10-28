#pragma once

class WalkerEnemy;

class IWalkerEnemyState
{
public:
	IWalkerEnemyState() = default;
	virtual ~IWalkerEnemyState() = default;

	virtual void Enter(WalkerEnemy&) = 0;
	virtual void Update(WalkerEnemy&) = 0;
	virtual void Exit(WalkerEnemy&) = 0;
	virtual const char* GetStateName() const = 0;
};