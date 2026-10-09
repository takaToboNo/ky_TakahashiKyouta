#include "Enemy.h"

void Enemy::Initialize()
{
	Character::Initialize();
	m_Layer = Layer::Enemy;
}

void Enemy::Finalize()
{
	Character::Finalize();
}

void Enemy::Destroy()
{
	Character::Destroy();
}
