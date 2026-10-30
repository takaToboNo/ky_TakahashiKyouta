#include "WalkerEnemyMove.h"
#include "WalkerEnemy.h"

void WalkerEnemyMove::Enter(WalkerEnemy& walkerEnemy)
{
}

void WalkerEnemyMove::Update(WalkerEnemy& walkerEnemy)
{
	walkerEnemy.SetColor(RED);

	Vector2 direction = walkerEnemy.GetAttachDirection();
	walkerEnemy.IsClockwise() ? direction.RotateClockwise90() : direction.RotateCounterClockwise90();
	walkerEnemy.SetMoveDirection(direction);

	if (!walkerEnemy.IsAttached())
	{
		walkerEnemy.RequestState(EWalkerEnemyState::Fall);
	}
}

void WalkerEnemyMove::Exit(WalkerEnemy& walkerEnemy)
{
	walkerEnemy.SetMoveDirection(Vector2::Zero());
}
