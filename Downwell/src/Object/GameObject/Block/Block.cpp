#include "Block.h"

void Block::Initialize()
{
	GameObject::Initialize();
	m_Tag = Tag::Block;
	m_Layer = Layer::Block;
	m_Scale = { BLOCK_SIZE,BLOCK_SIZE };
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
