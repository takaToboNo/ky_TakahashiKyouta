#include "SolidBlock.h"

//‰¼
#include "DxLib.h"

void SolidBlock::Initialize()
{
	Block::Initialize();
	m_Tag = Tag::Block;
}

void SolidBlock::Finalize()
{
	Block::Finalize();
}

void SolidBlock::Update(float dt)
{
	Block::Update(dt);
}

void SolidBlock::Draw()
{
	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f));
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f));
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f));
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f));

	DrawBox(x1, y1, x2, y2, GetColor(WHITE.r, WHITE.g, WHITE.b), TRUE);
}

void SolidBlock::Destroy()
{
	Block::Destroy();
}

void SolidBlock::OnCollision(GameObject* other, const HitInfo& hitInfo)
{
}
