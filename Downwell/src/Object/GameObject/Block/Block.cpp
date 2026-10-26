#include "Block.h"
#include "GameHelper.h"

void Block::Initialize()
{
	GameObject::Initialize();
	m_Tag = Tag::Block;
	m_Layer = Layer::Block;
	m_Scale = { TILE_SIZE,TILE_SIZE };
	m_Color = BLOCK_COLOR;
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
