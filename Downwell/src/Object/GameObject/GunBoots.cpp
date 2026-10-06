#include "GunBoots.h"

//‰¼
#include <cassert>
#include "Main.h"

void GunBoots::Initialize()
{
	GameObject::Initialize();
	m_Position = { 200.0f,400.0f };
	m_Scale = { 25.0f,20.0f };
	
}

void GunBoots::Finalize()
{
	GameObject::Finalize();
}

void GunBoots::Update()
{
	float dt = 1.0f / 60.0f;
}

void GunBoots::Draw()
{
	float x1, y1;
	x1 = m_Position.x - (m_Scale.x * 0.5f);
	y1 = m_Position.y - (m_Scale.y * 0.5f);
	float x2, y2;
	x2 = m_Position.x + (m_Scale.x * 0.5f);
	y2 = m_Position.y + (m_Scale.y * 0.5f);

	int result = DrawBox(x1, y1, x2, y2, GetColor(255, 255, 0), TRUE);

	assert(result == 0);
}

void GunBoots::Destroy()
{
	GameObject::Destroy();
}

bool GunBoots::CreateBullet()
{
	return false;
}
