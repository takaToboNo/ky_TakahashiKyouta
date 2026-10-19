#include "Enemy.h"

void Enemy::Initialize()
{
	Character::Initialize();
	m_Tag = Tag::Enemy;
	m_Layer = Layer::Enemy;
}

void Enemy::Finalize()
{
	Character::Finalize();
}

void Enemy::Update(float dt)
{
	Character::Update(dt);
}

void Enemy::Destroy()
{
	Character::Destroy();
}
