#include "GunBoots.h"

//‰¼
#include "DxLib.h"

void GunBoots::Initialize()
{
	GameObject::Initialize();
	m_Position = { 200.0f,400.0f };
	m_Scale = { 25.0f,20.0f };
	m_Color = YELLOW;

	for (auto& bullet : m_pBullets)
	{
		bullet->Initialize();
	}
	
}

void GunBoots::Finalize()
{
	for (auto& bullet : m_pBullets)
	{
		bullet->Finalize();
	}

	GameObject::Finalize();
}

void GunBoots::Update()
{
	for (auto& bullet : m_pBullets)
	{
		bullet->Update();
	}

	for (auto it = m_pBullets.begin(); it != m_pBullets.end();)
	{
		if (!(*it)->IsActive())
		{
			Release(std::move(*it));
			it = m_pBullets.erase(it);
		}
		else
		{
			++it;
		}
	}

	//float dt = 1.0f / 60.0f;

	//’e”­ŽË
	if (CheckHitKey(KEY_INPUT_B))
	{
		auto bullet = Acquire();
		bullet->Initialize();
		m_pBullets.push_back(std::move(bullet));
	}
}

void GunBoots::Draw()
{
	for (auto& bullet : m_pBullets)
	{
		bullet->Draw();
	}

	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f));
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f));
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f));
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f));

	DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);
}

void GunBoots::Destroy()
{
	GameObject::Destroy();
}

bool GunBoots::CreateBullet()
{
	return false;
}
