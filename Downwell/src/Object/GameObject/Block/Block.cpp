#include "Block.h"

void Block::Initialize()
{
	GameObject::Initialize();
	m_Layer = Layer::Block;
	m_Scale = { 30.0f,30.0f };
}

void Block::Finalize()
{
	GameObject::Finalize();
}

void Block::Update(float dt)
{
	GameObject::Update(dt);
}

void Block::Destroy()
{
	GameObject::Destroy();
}
