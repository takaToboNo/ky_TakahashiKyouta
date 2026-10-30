#include "WalkerEnemyFall.h"
#include "WalkerEnemy.h"

void WalkerEnemyFall::Enter(WalkerEnemy& walkerEnemy)
{
	walkerEnemy.SetVelocity(Vector2::Zero());
}

void WalkerEnemyFall::Update(WalkerEnemy& walkerEnemy)
{
	walkerEnemy.SetColor(DEBUG_COUNT_COLOR);

	if (walkerEnemy.IsAttached())
	{
		walkerEnemy.RequestState(EWalkerEnemyState::Move);
	}
}

void WalkerEnemyFall::Exit(WalkerEnemy& walkerEnemy)
{
}
